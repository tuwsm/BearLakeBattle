For info and instructions about this repo, read ./AGENTS.md

## 플러그인 바이너리 규칙

이 프로젝트는 `Source/`가 없는 블루프린트 프로젝트라서, 에디터가 플러그인 C++ 코드를 직접 빌드할 수 없다.
팀원들은 Diversion으로 받은 플러그인 DLL을 그대로 쓰므로 `Plugins/*/Binaries/`는 반드시 커밋되어야 한다.

- C++ 플러그인을 새로 추가할 때: 플러그인 폴더 안에 자체 `.gitignore`가 있는지 확인하고, `Binaries`를 무시하는 줄이 있으면 지운다. (Diversion은 하위 폴더의 `.gitignore`도 따른다.)
- 커밋 전에 `dv status`로 `Binaries/Win64/`의 `.dll`과 `UnrealEditor.modules`가 목록에 있는지 확인한다. `dv status <파일>`은 무시된 파일도 "Synced"로 표시하므로 그것만으로 판단하지 말고, `dv diff --name-status`나 커밋 내역으로 확인한다.
- 플러그인 C++ 코드를 수정해 다시 빌드했다면, 새로 생긴 DLL과 `.modules`도 같이 커밋한다.
- 팀원 PC에서 "Engine modules are out of date"가 뜨면 대부분 플러그인 DLL이 빠졌거나 엔진 버전이 다른 것이다. 엔진은 UE 5.6.1을 쓴다.
