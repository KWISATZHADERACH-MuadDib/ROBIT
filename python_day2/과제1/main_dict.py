import csv
import json


INPUT_FILE = "students.csv"
CLEAN_FILE = "clean_students.csv"
SUMMARY_FILE = "summary.json"


def load_and_clean(input_path):
    valid_rows = []

    try:
        with open(input_path, "r", encoding="utf-8", newline="") as f:
            reader = csv.DictReader(f)  # 첫 행을 자동으로 header(필드명)로 사용

            for line_no, row in enumerate(reader, start=2):
                name = row.get("name")
                score_str = row.get("score")

                if name is None or score_str is None:
                    print(f"[{line_no}행] 오류: 필요한 열이 없습니다 -> {row}")
                    continue

                try:
                    score = int(score_str)
                except ValueError:
                    print(f"[{line_no}행] 오류: '{score_str}' 를 숫자로 변환할 수 없습니다 (name={name})")
                    continue

                if not (0 <= score <= 100):
                    print(f"[{line_no}행] 오류: score={score} 가 허용 범위(0~100)를 벗어났습니다 (name={name})")
                    continue

                valid_rows.append({"name": name, "score": score})

    except FileNotFoundError:
        print(f"오류: '{input_path}' 파일을 찾을 수 없습니다.")

    return valid_rows


def save_clean_csv(rows, output_path):
    with open(output_path, "w", encoding="utf-8", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=["name", "score"])
        writer.writeheader()
        writer.writerows(rows)
    print(f"\n유효한 데이터 {len(rows)}건을 '{output_path}' 에 저장했습니다.")


def save_summary_json(rows, output_path):
    count = len(rows)
    scores = [r["score"] for r in rows]

    if count > 0:
        average = round(sum(scores) / count, 2)
        top = max(rows, key=lambda r: r["score"])
        top_name, top_score = top["name"], top["score"]
    else:
        average = 0
        top_name, top_score = None, None

    summary = {
        "count": count,
        "average": average,
        "top_student": top_name,
        "top_score": top_score,
    }

    with open(output_path, "w", encoding="utf-8") as f:
        json.dump(summary, f, ensure_ascii=False, indent=2)

    print(f"요약 정보를 '{output_path}' 에 저장했습니다.")
    print(json.dumps(summary, ensure_ascii=False, indent=2))


def main():
    print("=== 학생 성적 CSV 처리 시작 (DictReader/DictWriter 버전) ===\n")
    valid_rows = load_and_clean(INPUT_FILE)

    if valid_rows:
        save_clean_csv(valid_rows, CLEAN_FILE)
        save_summary_json(valid_rows, SUMMARY_FILE)
    else:
        print("\n저장할 유효한 데이터가 없습니다.")


if __name__ == "__main__":
    main()
