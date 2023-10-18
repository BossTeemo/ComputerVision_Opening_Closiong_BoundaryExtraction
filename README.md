# ComputerVision_Opening_Closiong_BoundaryExtraction
---
이 프로젝트는 이미지 처리 분야에서의 모폴로지 연산인 Opening, Closing 및 Boundary Extraction을 구현한 프로그램입니다.

## 기능

- **Opening**: 이 연산은 노이즈 제거를 위해 주로 사용됩니다. Erosion을 수행한 후 Dilation을 수행하여 원래 이미지의 작은 노이즈나 결점을 제거합니다.
- **Closing**: 이 연산은 이미지 내의 작은 홀을 채우는 데 사용됩니다. Dilation을 수행한 후 Erosion을 수행합니다.
- **Boundary Extraction**: 이미지의 경계를 추출하는 기능입니다. 이미지에서 Erosion된 이미지를 빼거나 Dilation된 이미지에서 원본 이미지를 빼는 방식으로 구현됩니다.

## 사용법

1. 프로그램을 실행합니다.
2. 원하는 이미지를 불러옵니다.
3. 상단의 버튼을 사용하여 Opening, Closing, Boundary Extraction 중 원하는 연산을 선택하고 실행합니다.
4. 결과 이미지가 새 창에서 나타납니다.

## 설치 및 실행

1. GitHub 저장소를 클론 또는 다운로드합니다.
2. Qt Creator에서 프로젝트를 열고 빌드합니다.
3. 생성된 실행 파일을 실행하여 프로그램을 시작합니다.

## 연락처

문제가 발생하거나 질문이 있을 경우 [GitHub Issue](https://github.com/BossTeemo/ComputerVision_Opening_Closing_BoundaryExtraction/issues)를 통해 문의해 주세요.

---

This project implements the morphological operations, Opening, Closing, and Boundary Extraction, used in image processing.

## Features

- **Opening**: This operation is primarily used for noise reduction. It performs Erosion followed by Dilation, eliminating minor noise or imperfections in the original image.
- **Closing**: This operation is used to fill minor holes within the image. It performs Dilation followed by Erosion.
- **Boundary Extraction**: This feature extracts the boundaries of an image. It is implemented by subtracting the Eroded image from the original or by subtracting the original image from the Dilated image.

## Usage

1. Launch the program.
2. Load your desired image.
3. Use the buttons on the top to select and execute the desired operation: Opening, Closing, or Boundary Extraction.
4. The resulting image will appear in a new window.

## Installation & Running

1. Clone or download the GitHub repository.
2. Open the project in Qt Creator and build it.
3. Run the generated executable to start the program.

## Contact

If you encounter any issues or have questions, please raise them on the [GitHub Issue](https://github.com/BossTeemo/ComputerVision_Opening_Closing_BoundaryExtraction/issues) section.

---
