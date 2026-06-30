# CS230 Final Project

DigiPen Institute of Technology **CS230** 수업에서 직접 제작한 C++ 게임 엔진과 3개의 플레이 가능한 게임 모드입니다. 저수준 그래픽/입력 처리는 수업에서 제공된 **Doodle** 라이브러리를 사용했습니다.

<div align="center">

[![C++](https://img.shields.io/badge/C%2B%2B-Engine-00599C?logo=cplusplus&logoColor=white)](#)
[![DigiPen](https://img.shields.io/badge/DigiPen-CS230-orange)](#)
[![Doodle](https://img.shields.io/badge/Framework-Doodle-blueviolet)](#)

</div>


> **제작자:** Hyunjun Lee, Geumbi Yeo
> **수업:** CS230 (DigiPen Institute of Technology)
> **언어:** C++
> **렌더링/입력 라이브러리:** [doodle](https://github.com/DigiPen-Faculty/Doodle) (수업 제공 프레임워크)

---

## 목차

- [개요](#개요)
- [엔진 아키텍처](#엔진-아키텍처)
- [공통 조작법](#공통-조작법)
- [게임 모드](#게임-모드)
  - [1. 사이드 스크롤러 (Mode 1)](#1-사이드-스크롤러-mode-1)
  - [2. 스페이스 슈터 (Mode 2)](#2-스페이스-슈터-mode-2)
  - [3. Watch Your Step (Mode 3)](#3-watch-your-step-mode-3)
- [승리 / 게임 오버 조건 요약](#승리--게임-오버-조건-요약)
- [크레딧](#크레딧)

---

## 개요

이 프로젝트는 CS230 수업을 위해 직접 제작한 컴포넌트 기반 2D 게임 엔진 위에 만들어진 미니 게임 모음입니다. 엔진은 윈도우 생성, 입력 처리, 스프라이트/애니메이션 재생, 충돌 판정, 카메라 제어, 파티클 시스템, 게임 상태(스크린) 관리 등을 담당합니다. 이 엔진 위에 메인 메뉴에서 선택 가능한 3가지 서로 다른 게임 모드를 구현했습니다.

| 모드 | 게임 내 이름 | 장르 | 구현 방식 | 제작 형태 |
|---|---|---|---|---|
| Mode 1 | **Side Scroller** | 2D 플랫포머 | 교수님이 주신 기능 명세서를 보고 구현 | 개인 과제 — 이 리포지토리는 **이현준**의 구현 버전 사용 |
| Mode 2 | **Space Shooter** | 탑다운 슈팅 (Asteroids 스타일) | 교수님이 주신 기능 명세서를 보고 구현 | 개인 과제 — 이 리포지토리는 **이현준**의 구현 버전 사용 |
| Mode 3 | **Watch Your Step** | 수직 플랫포머 / "클라이밍" | 직접 기획부터 구현까지 전부 진행 | 이현준 & 여금비가 **함께** 제작 |

> 📝 Mode 1(Side Scroller)과 Mode 2(Space Shooter)는 원래 **개인 과제**였습니다 — 같은 영문 기능 명세서(교수님 제공)를 보고 각자 따로 본인만의 버전을 구현했습니다. 이 리포지토리에서는 **이현준**이 개인적으로 구현한 Mode 1, Mode 2 버전을 기반으로 사용합니다. **Mode 3(Watch Your Step)** 는 별도의 명세서 없이, 처음부터 끝까지 이현준과 여금비가 **함께** 기획하고 구현한 스테이지입니다.

---

## 엔진 아키텍처

엔진(`CS230` 네임스페이스)은 컴포넌트 기반 구조를 따릅니다.

- **`Engine`** — 모든 엔진 서브시스템(Input, Window, Logger, GameStateManager, TextureManager, SpriteFonts)에 접근할 수 있는 싱글톤 서비스 로케이터입니다. 30FPS 고정 타임스텝 메인 루프를 실행합니다.
- **`GameStateManager` / `GameState`** — Splash, Main Menu, Mode 1, Mode 2, Mode 3, Win 등 상위 레벨 화면을 Load/Update/Unload 상태 머신으로 관리합니다.
- **`GameObject` / `GameObjectManager`** — 게임 내 모든 엔티티의 기본 클래스입니다. 위치/속도/회전/스케일을 지원하고, 객체별로 간단한 유한 상태 머신(`State`)을 가지며, 매 프레임 모든 객체 쌍에 대해 충돌 판정 및 처리를 수행합니다.
- **`Component` / `ComponentManager`** — `GameObject` 또는 `GameState`에 붙일 수 있는 범용 컴포넌트 시스템입니다(예: `Sprite`, `Collision`, `Camera`, `Gravity`, `Score`, `Timer`, `Background`, `ParticleEmitter`).
- **`Sprite` / `Animation`** — `.spt`(스프라이트 정보) 및 `.anm`(애니메이션 시퀀스) 텍스트 기반 에셋 파일을 불러와 프레임 재생을 처리합니다.
- **`Collision`** — `RectCollision`(사각형)과 `CircleCollision`(원형) 컴포넌트로 AABB 및 원-원 충돌 판정을 구현하며, 디버그용 충돌 박스 시각화 기능도 제공합니다.
- **`Camera` / `Camera2`** — 횡스크롤용/종스크롤용 카메라로, 지정된 범위 내에서 타겟 오브젝트를 따라갑니다.
- **`ParticleEmitter`** — 오브젝트 풀링 기반 파티클 시스템으로, 연기, 타격 이펙트, 잔해, 으스러짐(crush) 이펙트 등에 사용됩니다.
- **`Input` / `InputKey`** — Doodle의 키보드 콜백 위에 구현된 키보드 입력 상태 래퍼입니다(`IsKeyDown`, `IsKeyReleased`).
- **`SpriteFont` / `Texture` / `TextureManager`** — 비트맵 폰트 렌더링과 텍스처 로딩/캐싱을 담당합니다.

---

## 공통 조작법

아래 조작법은 메인 메뉴 및 모든 게임 모드에 공통적으로 적용됩니다 (모드별 조작법은 각 섹션 참고).

| 키 | 동작 |
|---|---|
| **↑ / ↓ (방향키 위/아래)** | 메뉴 항목 이동 |
| **Enter** | 메뉴 선택 확인 |
| **Escape** | (게임 중) 메인 메뉴로 복귀 |
| **R** | 현재 스테이지 재시작 |
| **~ (틸드)** | *(디버그 빌드 한정)* 충돌 박스 시각화 On/Off |

### 메인 메뉴 항목

| 항목 | 이동 위치 |
|---|---|
| Side Scroller | Mode 1 |
| Space Shooter | Mode 2 |
| Watch Your Step | Mode 3 |
| Quit | 게임 종료 |

---

## 게임 모드

### 1. 사이드 스크롤러 (Mode 1)

> **구현 방식:** 원래 개인 과제였으며, 교수님이 주신 기능 명세서를 보고 구현. 이 리포지토리는 **이현준**의 버전을 사용.

<div align="center">
<table>
<tr>
<td align="center" width="50%"><img src="https://github.com/user-attachments/assets/a4d38be8-d4fe-440b-bcef-3b05d910f027" width="100%"/><br/><sub><b>게임플레이 전반</b></sub></td>
<td align="center" width="50%"><img src="https://github.com/user-attachments/assets/35d45ddc-9d41-408d-a83b-63f70e172953" width="100%"/><br/><sub><b>점프 액션</b></sub></td>
</tr>
<tr>
<td align="center" width="50%"><img src="https://github.com/user-attachments/assets/ee70b4fd-5349-4025-88f4-02d1dd2726a8" width="100%"/><br/><sub><b>적과의 조우</b></sub></td>
<td align="center" width="50%"><img src="https://github.com/user-attachments/assets/12180d65-fd2e-45c3-ae1a-487aa3c68a6b" width="100%"/><br/><sub><b>레벨 클리어</b></sub></td>
</tr>
</table>
</div>

#### 게임 설명
가로 스크롤 방식의 2D 플랫포머입니다. 플레이어는 **Hero**를 조작하여 달리고 점프하며, 튕기는 **Ball**, 순찰하는 **Bunny** 적, **TreeStump** 장애물 등이 가득한 레벨을 통과해 제한 시간 안에 **Exit**에 도달해야 합니다.

카메라는 Hero를 수평으로 따라가며, 서로 다른 속도로 스크롤되는 패럴랙스 배경(구름, 산, 전경 레이어)으로 입체감을 줍니다.

#### 조작법

| 키 | 동작 |
|---|---|
| **← / →** | Hero 좌/우 이동 |
| **↑** | 점프 |
| **Escape** | 메인 메뉴로 복귀 |
| **R** | 스테이지 재시작 |

#### Hero 상태(State)
- **Idle** — 정지 상태
- **Running** — 좌/우 이동 중
- **Skidding** — 빠른 속도에서 방향을 반대로 전환할 때 감속하는 상태
- **Jumping** — 점프 입력 후 상승 중
- **Falling** — 바닥에 닿지 않고 하강 중

#### 장애물 및 상호작용 오브젝트

| 오브젝트 | 동작 |
|---|---|
| **Ball** | 바닥 위에서 중력에 의해 계속 튕깁니다. 측면에서 Hero와 충돌하면 Hero를 밀쳐내고 잠시 무적/깜빡임("피격") 상태가 됩니다. |
| **Bunny** | 고정된 두 X좌표("순찰 노드") 사이를 왕복하며 순찰합니다. 순찰 경로 내에서 Hero를 감지하면 2배 속도로 돌진(공격)합니다. 위에서 밟으면 처치(+100점)되며 연기 파티클이 발생하고, 측면에서 충돌하면 Hero가 밀쳐지며 피격 상태에 들어갑니다. |
| **TreeStump** | 다양한 크기의 정적 장애물/발판으로, Hero가 위에 올라서거나 측면에서 충돌할 수 있습니다. |
| **Floor** | 레벨의 보행 가능한 지형을 구성하는 정적 바닥 충돌 구역입니다. |
| **Exit** | 레벨 끝에 있는 트리거 영역입니다. Hero가 닿으면(이 빌드 기준) 메인 메뉴로 돌아가며, Mode 3의 Player 캐릭터가 닿으면 Win 화면으로 이동합니다. |

#### HUD
- **Score** (좌측 상단) — 적을 처치하면 증가
- **Lives** (중앙 상단) — 3에서 시작
- **Timer** (우측 상단) — 60초에서 시작하여 카운트다운

#### 클리어 / 게임 오버 조건

| 조건 | 결과 |
|---|---|
| Hero가 레벨의 **Exit**에 닿음 | 메인 메뉴로 복귀 |
| **타이머가 0이 됨** | 목숨 1개 차감, 남은 목숨이 있으면 스테이지 재시작 |
| **레벨 하단으로 추락** (`y < -300`) | 사망 처리, 목숨 1개 차감, 남은 목숨이 있으면 스테이지 재시작 |
| **목숨이 0이 됨** | 목숨이 3으로 초기화되며 메인 메뉴로 복귀 |

---

### 2. 스페이스 슈터 (Mode 2)

> **구현 방식:** 원래 개인 과제였으며, 교수님이 주신 기능 명세서를 보고 구현. 이 리포지토리는 **이현준**의 버전을 사용.

<div align="center">
<table>
<tr>
<td align="center" width="33.3%"><img src="https://github.com/user-attachments/assets/42136651-ed95-4f51-98c8-2ad944cc4620" width="100%"/><br/><sub><b>비행 & 추진</b></sub></td>
<td align="center" width="33.3%"><img src="https://github.com/user-attachments/assets/b4031e77-2b7a-4759-8c8a-2cdc779164bf" width="100%"/><br/><sub><b>전투</b></sub></td>
<td align="center" width="33.3%"><img src="https://github.com/user-attachments/assets/21993425-6604-4eb4-a191-3552adc460b9" width="100%"/><br/><sub><b>운석 지대</b></sub></td>
</tr>
</table>
</div>

#### 게임 설명
탑다운 방식의 *Asteroids* 스타일 슈팅 게임입니다. 플레이어는 회전 및 추진력 기반으로 조작하는 **Ship**을 조종하여, 화면 경계를 넘어가면 반대편으로 재출현(wrap)하는 아레나 안에서 분열하는 **Meteor**들과 플레이어를 능동적으로 추격하는 AI **EnemyShip**을 격파해야 합니다.

#### 조작법

| 키 | 동작 |
|---|---|
| **A** | 반시계 방향 회전 |
| **D** | 시계 방향 회전 |
| **W** | 현재 바라보는 방향으로 추진(가속) |
| **Space** | 양쪽 레이저 발사 |
| **R** | Ship 파괴 후 스테이지 재시작 |
| **Escape** | *(디버그 빌드 한정)* 메인 메뉴로 복귀 |

#### 비행 모델
- Ship은 자유롭게 회전하며, 현재 바라보는 방향으로만 가속됩니다(관성/드리프트 이동 + 드래그 적용).
- 속도는 최대치로 제한됩니다.
- 모든 오브젝트(Ship, Meteor)는 **화면 경계를 넘으면 반대편에서 다시 나타납니다**(스크린 랩).

#### 적 및 장애물

| 오브젝트 | 동작 |
|---|---|
| **Meteor** | 무작위 위치, 속도, 크기로 생성됩니다. 레이저에 맞으면 체력이 감소하며 타격 스파크와 암석 파편 파티클이 발생합니다. 큰 운석은 파괴될 때 (최소 크기가 아니라면) **두 개의 더 작은 운석으로 분열**되어 비스듬히 흩어지며, 가장 작은 크기는 점수를 주며 완전히 파괴됩니다. |
| **EnemyShip** | 플레이어 Ship을 지속적으로 회전하며 추격/추진하고, 양쪽에 화염 트레일 스프라이트가 표시됩니다. 플레이어 Ship과 충돌하면 Ship을 파괴합니다. 레이저로 파괴하면 점수를 획득하고 폭발 애니메이션이 재생됩니다. |
| **Laser** | Ship의 양쪽 발사구에서 Ship이 현재 바라보는 방향으로 발사됩니다. 화면 밖으로 나가면 자동으로 소멸합니다. Meteor와 EnemyShip을 파괴할 수 있습니다. |

#### HUD
- **Score** (좌측 하단) — Meteor와 EnemyShip을 파괴하면 증가
- Ship이 파괴되면 화면 중앙에 **"Game Over" / "Press R to restart"** 배너가 표시됨

#### 클리어 / 게임 오버 조건

| 조건 | 결과 |
|---|---|
| Ship이 **Meteor** 또는 **EnemyShip**과 충돌 | Ship 파괴, "Game Over" 표시 |
| Game Over 상태에서 **R** 입력 | 스테이지 재시작 |

> 참고: 이 모드는 기본적으로 스코어 어택/생존형 게임 방식이며, 별도의 명시적인 "승리" 조건은 없습니다. 목표는 최대한 오래 생존하며 점수를 높이는 것입니다.

---

### 3. Watch Your Step (Mode 3)

> **구현 방식:** 교수님이 주신 명세서 없이, 이현준과 여금비가 **함께** 기획하고 구현

<div align="center">
<table>
<tr>
<td align="center" width="50%"><img src="https://github.com/user-attachments/assets/a1fd819b-bd03-47c1-b9a6-140eed0aa612" width="100%"/><br/><sub><b>구름 점프</b></sub></td>
<td align="center" width="50%"><img src="https://github.com/user-attachments/assets/99b04def-7af9-424e-818f-a173db6ee10c" width="100%"/><br/><sub><b>하늘 오르기</b></sub></td>
</tr>
</table>
</div>

#### 게임 설명
*Doodle Jump* / *Icy Tower* 스타일의 수직 스크롤 플랫포머("클라이밍" 게임)입니다. 플레이어는 **Player** 캐릭터를 조작하여, 길게 수작업으로 배치된 수직 방향의 **Cloud**(구름) 발판들을 점프로 이어가며 위로 올라가야 합니다. 위험 요소인 **LightningCloud**(번개 구름)와 순찰하는 **Bird**를 피하거나 역이용하면서, 떨어지지 않고 제한 시간 안에 레벨 최상단의 **Exit**에 도달해야 합니다.

카메라(`Camera2`)는 플레이어를 수직으로 따라가며, 레벨 높이 범위 내로 제한됩니다.

#### 조작법

| 키 | 동작 |
|---|---|
| **← / →** | Player 좌/우 이동 |
| **↑** | 점프 |
| **Escape** | (사망 상태가 아닐 때) 메인 메뉴로 복귀 |
| **R** | (사망 상태가 아닐 때) 스테이지 재시작 |

#### Player 상태(State)
- **Idle** — 구름 위에서 정지 상태
- **Running** — 좌/우 이동 중
- **Skidding** — 빠른 속도에서 방향을 반대로 전환할 때 감속하는 상태
- **Jumping** — 점프 입력 후 상승 중
- **Falling** — 발판이 없어 하강 중

#### 장애물 및 상호작용 오브젝트

| 오브젝트 | 동작 |
|---|---|
| **Cloud** | 4가지 시각적 크기/타입이 존재합니다. 일반 발판 역할을 하며, 낙하 중 위에서 착지하면 "crush" 파티클이 발생하며 플레이어가 그 위에 설 수 있습니다. 아래나 측면에서 충돌하면 수평 이동이 막힙니다. |
| **LightningCloud** | 위험한 구름 변형입니다. 낙하 중 위에서 착지해도 발판처럼 설 수 **없으며**, 대신 플레이어를 **위쪽으로 강하게 튕겨 올리고**(부스트 점프) 약간의 점수를 추가로 줍니다. 측면에서 충돌하면 Bird와 동일하게 이동이 막히고 잠깐 피격/넉백 상태가 됩니다. |
| **Bird** | 고정된 두 Y좌표("순찰 노드") 사이를 왕복 순찰하며, 순찰 경로 상에서 플레이어가 접근하는 것을 감지하면 2배 속도로 돌진(공격)합니다. 위에서 밟으면 처치되어 점수를 획득하고 일반 점프와 비슷한 도약력을 얻으며, 측면에서 충돌하면 플레이어가 밀쳐지며 피격/깜빡임 상태에 들어갑니다. |
| **Exit** | 클라이밍 구간 최상단에 배치된 트리거 영역입니다. **Player** 캐릭터가 닿으면 **Win 화면**으로 이동합니다. |

#### HUD
- **Score** (좌측 하단) — Bird 처치 및 LightningCloud 바운스로 증가
- **Lives** (중앙 하단) — 5에서 시작
- **Timer** (우측 하단) — 120초에서 시작하여 카운트다운
- Player가 사망했거나 목숨이 모두 소진되면 HUD 요소들은 숨겨짐

#### 클리어 / 게임 오버 조건

| 조건 | 결과 |
|---|---|
| Player가 클라이밍 구간 최상단의 **Exit**에 도달 | **Win 화면**으로 이동 |
| **타이머가 0이 됨** | 목숨 1개 차감, 남은 목숨이 있으면 스테이지 재시작 |
| **레벨 하단으로 추락** (`y < -280`) | 사망 처리, 목숨 1개 차감, 남은 목숨이 있으면 스테이지 재시작 |
| **목숨이 0이 됨** | "Game Over" 배너 표시, **Escape** 입력 시 메인 메뉴로 복귀(목숨은 5로 초기화) |

---

## 승리 / 게임 오버 조건 요약

| 화면 | 발생 조건 |
|---|---|
| **Win 화면** | Mode 3의 **Player** 캐릭터로 Exit에 도달했을 때 (예: Watch Your Step 클리어) |
| **메인 메뉴 (Exit 경유)** | Mode 1의 **Hero** 캐릭터로 Exit에 도달했을 때 |
| **메인 메뉴 (게임 오버 경유)** | Mode 1 또는 Mode 3에서 목숨을 모두 소진했을 때 |
| **재시작 (R 키)** | 모든 모드에서 현재 스테이지를 다시 불러올 때 사용 가능 |

**Win** 화면 자체에도 별도의 하위 메뉴가 있습니다.

| 항목 | 이동 위치 |
|---|---|
| Main Menu | 메인 메뉴로 복귀 |
| Side Scroller | Mode 1 |
| Space Shooter | Mode 2 |
| Quit | 게임 종료 |

---

## 크레딧

- **엔진:** Hyunjun Lee, Geumbi Yeo
- **Mode 1 (Side Scroller) & Mode 2 (Space Shooter):** 원래 각자 따로 진행한 개인 과제로, 수업에서 제공된 기능 명세서를 보고 각각 구현. 이 리포지토리는 **이현준**이 개인적으로 구현한 두 모드의 버전을 사용.
- **Mode 3 (Watch Your Step):** 이현준과 여금비가 **함께** 기획하고 구현한 오리지널 콘텐츠
- **프레임워크:** DigiPen CS230 수업에서 제공된 [Doodle](https://github.com/DigiPen-Faculty/Doodle) 그래픽/입력 라이브러리 기반
- **수업:** CS230, DigiPen Institute of Technology
