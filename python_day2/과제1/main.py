
import csv
import json


INPUT_FILE = "students.csv"
CLEAN_FILE = "clean_students.csv"
SUMMARY_FILE = "summary.json"


def load_and_clean(input_path):
    """CSV를 읽어서 유효한 (name, score) 리스트를 반환한다."""
    valid_rows = []

    try:
        with open(input_path, "r", encoding="utf-8", newline="") as f:
            reader = csv.reader(f)

            header = next(reader, None)  # 1) 첫 행(header)은 건너뛴다
            if header is None:
                print("파일이 비어 있습니다.")
                return valid_rows

            for line_no, row in enumerate(reader, start=2):  # 2번째 줄부터 데이터
                if not row:
                    continue  # 빈 줄은 무시

                if len(row) < 2:
                    print(f"[{line_no}행] 오류: 열 개수가 부족합니다 -> {row}")
                    continue

                name, score_str = row[0], row[1]

                try:
                    score = int(score_str)  # 2) int 변환 시도
                except ValueError:
                    print(f"[{line_no}행] 오류: '{score_str}' 를 숫자로 변환할 수 없습니다 (name={name})")
                    continue

                if not (0 <= score <= 100):  # 2) 범위 검사
                    print(f"[{line_no}행] 오류: score={score} 가 허용 범위(0~100)를 벗어났습니다 (name={name})")
                    continue

                valid_rows.append((name, score))  # 4) 유효한 행만 저장

    except FileNotFoundError:
        print(f"오류: '{input_path}' 파일을 찾을 수 없습니다.")

    return valid_rows


def save_clean_csv(rows, output_path):
    """유효한 행들을 clean_students.csv 로 저장한다."""
    with open(output_path, "w", encoding="utf-8", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(["name", "score"])
        for name, score in rows:
            writer.writerow([name, score])
    print(f"\n유효한 데이터 {len(rows)}건을 '{output_path}' 에 저장했습니다.")


def save_summary_json(rows, output_path):
    """인원수, 평균, 최고점을 summary.json 으로 저장한다."""
    count = len(rows)
    scores = [score for _, score in rows]

    if count > 0:
        average = round(sum(scores) / count, 2)
        top_name, top_score = max(rows, key=lambda r: r[1])
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
    print("=== 학생 성적 CSV 처리 시작 ===\n")
    valid_rows = load_and_clean(INPUT_FILE)

    if valid_rows:
        save_clean_csv(valid_rows, CLEAN_FILE)
        save_summary_json(valid_rows, SUMMARY_FILE)
    else:
        print("\n저장할 유효한 데이터가 없습니다.")


if __name__ == "__main__":
    main()
