# philosopher

## 프로젝트 개요
- 고전 문제 “식사하는 철학자”를 통해 동시성, 상호배제, 교착상태 회피, 타이밍 제어를 학습합니다.
- 두 가지 구현을 제공합니다:
  - `philo/`: 스레드 + 뮤텍스 기반
  - `philo_bonus/`: 프로세스 + 세마포어 기반

## 디렉토리 구성
- `philo/`
  - `main.c`: 인자 파싱, 초기화, 스레드 시작 및 종료, 모니터링
  - `philo.c`: 모니터링 루프, 종료 조건(is_dead, is_full), 스레드 시작
  - `act.c`: 철학자 상태(EAT, SLEEP, THINK) 전환과 행동 로직
  - `utils.c`: 시간/출력/입력검증(ft_atoi, get_time, psleep, prints 등)
  - `philo.h`: 구조체 정의(`t_info`, `t_philo`) 및 상수/선언
  - `Makefile`: `make`, `clean`, `fclean`, `re`
- `philo_bonus/`
  - `philo_bonus.c`: 인자 파싱, 초기화, 프로세스 생성/대기
  - `init_bonus.c`: 세마포어/타이밍 초기화
  - `run_bonus.c`: 철학자 프로세스 실행 루프 및 모니터링 스레드
  - `utils_bonus.c`: 에러 처리, 출력, 대기 시간, 안전 종료 등
  - `philo_bonus.h`: 구조체 정의와 상수/선언
  - `Makefile`: `make`, `clean`, `fclean`, `re`

## 빌드
- 기본 구현:
  - `cd philo && make` → 실행 파일 `philo`
- 보너스 구현:
  - `cd philo_bonus && make` → 실행 파일 `philo_bonus`

## 실행과 인자
- 공통 인자 형식: `<number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_must_eat]`
  - 예시(스레드 버전): `./philo 5 800 200 200 7`
  - 예시(보너스 버전): `./philo_bonus 5 800 200 200 7`
- 의미:
  - `number_of_philosophers`: 철학자 수
  - `time_to_die`: 마지막 식사 이후 죽기까지 시간(ms)
  - `time_to_eat`: 식사에 걸리는 시간(ms)
  - `time_to_sleep`: 잠자기에 걸리는 시간(ms)
  - `number_must_eat`(옵션): 각 철학자의 최소 식사 횟수(충족 시 종료)

## 핵심 동작
- 스레드 구현(`philo/`)
  - 각 철학자는 스레드로 실행되며, 포크는 `pthread_mutex_t` 배열로 모델링합니다.
  - `EAT → SLEEP → THINK` 순환, 짝수 철학자의 초기 대기(`psleep(info->t_eat / 2)`)로 교착 회피에 도움.
  - 출력은 `prints()`로 일관 관리(출력 뮤텍스), 사망/만복 상태는 전역 플래그와 보호 뮤텍스로 동기화합니다.
  - 모니터링 루프가 주기적으로 각 철학자의 사망 상태(마지막 식사 시각 대비 `time_to_die`)와 전체 만복(`is_full`)을 확인합니다.
- 보너스 구현(`philo_bonus/`)
  - 각 철학자는 별도 프로세스로 실행, 동기화는 네임드 세마포어(`fork`, `print`, `check_last_eat`)로 처리합니다.
  - 포크 세마포어를 두 번 획득 후 식사, `print` 세마포어로 출력 직렬화.
  - 각 프로세스 내부에서 모니터링 스레드가 사망 여부를 검사, 사망 시 `EXIT_FAILURE`로 종료하고 부모가 정리합니다.

## 입력 검증과 시간 처리
- `check_digit(argv)`: 숫자/`+` 위치 검증(스레드 버전)
- `ft_atoi`: 범위 체크 포함한 안전 변환(버전에 따라 음수/범위 처리 상이)
- `get_time/init_time`: 밀리초 단위 시간 획득(`gettimeofday`)
- `psleep/wait_time`: 바쁜 대기 없이 유연한 대기(ms)

## 사용 팁
- 단일 철학자 케이스: 오른손 포크가 없어 즉시 `time_to_die` 초과 시 사망 로그가 찍힐 수 있습니다.
- `number_must_eat` 미지정 시 무한 루프이며, 사망 또는 외부 종료로 마무리됩니다.
- 출력 라인은 “현재시각(ms) 철학자ID 상태” 형식으로 표준 출력에 기록됩니다.

## 예시 실행 로그(개념)
- `123 2 has taken a fork`
- `124 2 is eating`
- `325 2 is sleeping`
- `526 2 is thinking`
- `801 2 died`