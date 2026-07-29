**visual stduio code의 실행버튼으로 컴파일 했을때 오류가 발생하면 터미널에서 "python main.py"를 입력해 실행하시면 됩니다**

## 1. 선택한 라이브러리 : pygame (pygame-ce)

- **pygame** 은 파이썬으로 2D 게임을 만들 때 가장 널리 쓰이는 라이브러리입니다.
  창(윈도우) 띄우기, 도형/이미지 그리기, 마우스·키보드 입력 처리, 화면 갱신(게임 루프)을
  모두 지원합니다.
- 오셀로는 8x8 격자 보드 위에 흑돌/백돌을 놓는 게임이라, **보드(맵)를 그리고 클릭으로
  돌을 놓는 상호작용**이 핵심입니다. 이런 "게임판 그리기 + 마우스 클릭 처리"에
  가장 적합한 라이브러리가 pygame 이라 선택했습니다.
- 실제로는 원조 `pygame` 대신 **pygame-ce**(커뮤니티 에디션) 를 설치해서 사용했습니다.
  이유는 아래 3번 "문제 해결 과정"에 정리했습니다. 코드에서는 두 경우 모두
  동일하게 `import pygame` 으로 사용합니다.

### 설치 방법

```bash
pip install pygame-ce
```

(Python 3.13 이하를 사용 중이라면 원조 `pip install pygame` 도 문제없이 동작합니다.)

### 설치된 버전 확인

`main.py` 실행 시 콘솔에 설치된 버전이 자동으로 출력됩니다.

```
=== pygame 버전: 2.5.7 (SDL 2.32.10, Python 3.14.6) ===
```

버전만 따로 확인하고 싶다면:

```bash
pip show pygame-ce
```

또는

```bash
python -c "import pygame; print(pygame.version.ver)"
```

이 프로젝트는 **pygame-ce 2.5.7** / **Python 3.14.6** 환경에서 정상 동작을 확인했습니다.

---

## 2. 파일 구성

```
othello_project/
├── main.py             # pygame 을 활용한 오셀로 게임 실행 코드
├── requirements.txt      # pygame-ce 의존성 목록
└── README.md             # 이 문서 (수정 사항 및 문제 해결 과정 포함)
```

---

## 3. 문제 해결 과정 (Troubleshooting)

실제로 개발 및 설치 과정에서 겪었던 문제와 해결 방법을 순서대로 기록합니다.

### 문제 1 — SSL 인증서 오류
`pip install pygame` 실행 시 아래와 같은 오류 발생:
```
urllib.error.URLError: <urlopen error [SSL: CERTIFICATE_VERIFY_FAILED] certificate verify failed: certificate has expired>
```
- **원인 추정**: 시스템 시간 오차 또는 오래된 인증서 패키지(`certifi`)
- **시도한 해결책**: 시스템 시간 확인, `pip install --upgrade pip certifi`,
  `--trusted-host` 옵션으로 임시 우회 등을 시도

### 문제 2 — pygame 빌드(wheel) 실패
이후 아래와 같은 진짜 원인이 드러남:
```
error: subprocess-exited-with-error
Getting requirements to build wheel did not run successfully.
Skipping Cython compilation
```
- **원인**: 사용 중인 Python 버전이 **3.14**로, 원조 `pygame` (최신 안정 버전 2.6.1 기준)이
  아직 Python 3.14용 사전 빌드 wheel을 제공하지 않아 pip이 소스 코드를 직접
  컴파일하려다 실패한 것이었습니다.
- **처음 고려한 대안**: Python 3.12로 새 가상환경을 만드는 방법 (정석적이지만 번거로움)
- **채택한 해결책**: Python 재설치 없이, 같은 개발자들이 이어서 만드는 포크 버전인
  **pygame-ce** 를 대신 설치. pygame-ce 는 Python 3.14 wheel을 이미 제공하고 있었고,
  코드에서는 여전히 `import pygame` 그대로 사용 가능해 **`main.py` 수정 없이** 해결됨.

```bash
pip install pygame-ce
```

### 문제 3 — `ModuleNotFoundError: No module named 'pygame'`
pygame-ce 설치가 성공했는데도 `main.py` 실행 시 모듈을 못 찾는 오류 발생.
- **확인 과정**:
  1. `pip list` 로 실제 설치 여부 확인 → 정상 설치되어 있었음
  2. `where python` 으로 터미널이 사용하는 파이썬 경로 확인 → `.venv` 내부 경로가 맞았음
  3. 터미널에서 `python -c "import pygame"` 직접 실행 → **정상 동작 확인**
- **결론**: 문제는 pygame 자체가 아니라, **VS Code의 실행 버튼(▶ Run Python File)이
  터미널과 다른 Python 인터프리터를 사용**하고 있었기 때문이었습니다.
- **해결책**: 터미널에서 직접 `python main.py` 로 실행하거나,
  `Ctrl+Shift+P` → "Python: Select Interpreter" 에서 `.venv` 경로의 인터프리터를
  명시적으로 선택 후 실행.

### 문제 4 — Pylance의 `Import "pygame" could not be resolved` 경고
코드 편집기에서 노란색 경고가 표시됨.
- **원인**: 이 역시 VS Code의 코드 분석 도구(Pylance)가 `.venv` 가 아닌 다른 환경을
  기준으로 분석하고 있어서 발생한 것으로, **실제 실행에는 영향이 없는 경고**였습니다.
- **해결책**: 인터프리터를 `.venv` 로 맞추면 경고도 함께 사라짐 (선택 사항).

### 최종 requirements.txt
```
pygame-ce==2.5.7
```

## 4. main.py 기능 설명

1. **보드(맵) 그리기**: pygame 의 `pygame.draw.line`, `pygame.draw.circle` 을 이용해
   초록색 8x8 오셀로 보드와 흑/백 돌을 그린다.
2. **게임 로직**: 표준 오셀로 규칙을 순수 파이썬 함수로 구현
   - `valid_moves()` : 현재 차례에서 둘 수 있는 모든 칸 계산
   - `apply_move()` : 돌을 놓고 8방향으로 상대 돌을 뒤집는다
3. **마우스 인터랙션**: `pygame.MOUSEBUTTONDOWN` 이벤트로 클릭한 좌표를 보드 칸(행, 열)으로
   변환해 그 자리에 돌을 놓는다.
4. **힌트 표시**: 지금 클릭 가능한 칸에는 작은 초록 점을 그려 사용자에게 알려준다.
5. **턴/점수 표시**: 화면 상단에 현재 차례(흑/백)와 실시간 돌 개수를 표시한다.
6. **패스 처리**: 상대가 둘 곳이 없으면 자동으로 패스하고, 양쪽 다 둘 곳이 없으면
   게임을 종료하고 승자를 화면에 표시한다.
7. **다시하기**: 게임 종료 후 `R` 키를 누르면 새 게임을 시작할 수 있다.

---

## 5. 실행 방법

1) 라이브러리 설치

```bash
pip install -r requirements.txt
```

2) 실행 (터미널에서 직접 입력 권장 — VS Code ▶ 버튼은 인터프리터가 다를 수 있음)

```bash
python main.py
```

3) 조작 방법
   - 마우스 클릭: 돌 놓기 (초록 점이 있는 칸에만 놓을 수 있음)
   - 흑이 먼저 시작, 이후 번갈아 진행
   - 게임 종료 후 `R` 키: 새 게임 시작
   - 창 닫기 버튼(X): 게임 종료

---

## 6. requirements.txt 생성 방법

pygame-ce 설치 후 아래 명령으로 패키지 목록을 저장했습니다.

```bash
pip freeze > requirements.txt
```

> 프로젝트별로 가상환경을 분리하지 않으면 다른 과제에서 설치한 패키지까지
> 함께 기록될 수 있으니(문제 5 참고), `pip freeze` 실행 전 가상환경이
> 이 프로젝트 전용인지 확인하는 것을 권장합니다.

다른 컴퓨터에서 동일한 환경을 재현하려면:

```bash
pip install -r requirements.txt
```

---

## 7. 라이브러리에 대한 이해 (보고서)

- **pygame 이란?**
  SDL(Simple DirectMedia Layer) 이라는 C 라이브러리를 파이썬에서 사용할 수 있게 감싼 것으로,
  창 생성, 2D 그래픽, 사운드, 키보드/마우스 입력 처리를 제공하는 게임 개발용 라이브러리입니다.
  2000년에 처음 공개되어 지금까지도 활발히 유지보수되고 있는 성숙한(mature) 라이브러리입니다.

  더 빠른 릴리스와 새 Python 버전 지원을 위해 만든 것이 `pygame-ce`(Community Edition) 입니다.
  API는 동일해서 `import pygame` 그대로 사용할 수 있고, 최신 Python 버전 지원이
  더 빠른 편입니다. 이번 과제에서도 이 차이 덕분에 Python 3.14 환경에서
  별도의 Python 재설치 없이 문제를 해결할 수 있었습니다.
