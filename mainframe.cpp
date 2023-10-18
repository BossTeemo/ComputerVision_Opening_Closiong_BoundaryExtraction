#include "mainframe.h"
#include "ui_mainframe.h"
#include "imageform.h"
#include <QStringListModel>
#include <QFileDialog>
#include <QPainter>
#include <sstream>
#include <fstream>

using namespace std;

MainFrame::MainFrame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainFrame)
{
    ui->setupUi(this);

    _q_pFormFocused     = 0;

    //객체 맴버의 초기화


    //리스트 출력창을 안보이게
    ui->listWidget->setVisible(false);
    this->adjustSize();

    //UI 활성화 갱신
    UpdateUI();
}

MainFrame::~MainFrame()
{
    delete ui;

    for(auto& item : _lImageForm)
        delete item;

}

void MainFrame::CloseImageForm(ImageForm *pForm)
{
    //ImageForm 포인터 삭제
    unsigned int idx = std::find(_lImageForm.begin(), _lImageForm.end(), pForm) - _lImageForm.begin();
    if(idx != _lImageForm.size())
    {
        delete _lImageForm[idx];
        _lImageForm.erase(_lImageForm.begin() + idx);
    }

    //활성화 ImageForm 초기화
    _q_pFormFocused     = 0;

    //관련 객체 삭제

    //UI 활성화 갱신
    UpdateUI();
}

void MainFrame::UpdateUI()
{
    if(ui->tabWidget->currentIndex() == 0)
    {
    }
    else if(ui->tabWidget->currentIndex() == 1)
    {
    }
    else if(ui->tabWidget->currentIndex() == 2)
    {
    }
    else if(ui->tabWidget->currentIndex() == 3)
    {
    }
}

void MainFrame::OnMousePos(const int &nX, const int &nY, ImageForm* q_pForm)
{
}

void MainFrame::focusInEvent(QFocusEvent * event)
{
    Q_UNUSED(event) ;

    UpdateUI();
}

void MainFrame::closeEvent(QCloseEvent* event)
{
    //생성된 ImageForm을 닫는다.
    for(int i=0; i< _lImageForm.size(); i++)
        delete _lImageForm[i];

    //리스트에서 삭제한다.
    _lImageForm.clear();
}

void MainFrame::on_buttonOpen_clicked()
{
    // 이미지 파일 선택
    QFileDialog::Options q_Options = QFileDialog::DontResolveSymlinks | QFileDialog::DontUseNativeDialog;
    QString q_stFile = QFileDialog::getOpenFileName(this, tr("Select a Image File"), "./data", "Image Files(*.bmp *.ppm *.pgm *.png)", 0, q_Options);

    // 파일 선택이 취소되었는지 확인
    if(q_stFile.length() == 0)
        return;

    // 이미지 출력을 위한 ImageForm 생성
    ImageForm* q_pForm = new ImageForm(q_stFile, "OPEN", this);
    _lImageForm.push_back(q_pForm);

    // 원본 이미지 저장
    q_pForm->originalImage = q_pForm->ImageGray();

    // 임계값 처리 적용
    unsigned char threshold = 128;
    q_pForm->ImageGray().Threshold(threshold, q_pForm->thresholdedImage);

    // 이미지 업데이트
    q_pForm->Update(q_pForm->thresholdedImage);

    // ImageForm을 보여줌
    q_pForm->show();

    // UI 활성화 갱신
    UpdateUI();
}


void MainFrame::on_buttonDeleteContents_clicked()
{
    //생성된 ImageForm을 닫는다.
    for(int i=_lImageForm.size()-1; i>=0; i--)
        delete _lImageForm[i];

    //리스트에서 삭제한다.
    _lImageForm.clear();

    //객체 삭제


    ui->listWidget->clear();
}

void MainFrame::on_tabWidget_currentChanged(int index)
{
    static int nOld = -1;

    if(nOld == 0)
    {

    }
    else if(nOld == 1)
    {

    }
    nOld = index;

    //UI 활성화 갱신
    UpdateUI();
}

void MainFrame::on_buttonShowList_clicked()
{
    static int nWidthOld = ui->tabWidget->width();

    if(ui->listWidget->isVisible())
    {
        nWidthOld = ui->listWidget->width();
        ui->listWidget->hide();
        this->adjustSize();
    }
    else
    {
        ui->listWidget->show();
        QRect q_rcWin = this->geometry();

        this->setGeometry(q_rcWin.left(), q_rcWin.top(), q_rcWin.width()+nWidthOld, q_rcWin.height());
    }
}




int kernelSize = 3; // default value
int neighborType = 4; // default value

void MainFrame::on_select3by3_toggled(bool checked)
{
    if(checked) // ensure it's checked
        kernelSize = 3;
}

void MainFrame::on_select5by5_toggled(bool checked)
{
    if(checked) // ensure it's checked
        kernelSize = 5;
}

void MainFrame::on_select8N_toggled(bool checked)
{
    if(checked) // ensure it's checked
        neighborType = 8;
}

void MainFrame::on_select4N_toggled(bool checked)
{
    if(checked) // ensure it's checked
        neighborType = 4;
}




void MainFrame::on_pushOpening_clicked()
{
    if (!_q_pFormFocused)
        return;

    // 현재 활성화된 ImageForm의 이미지에 개방 연산 수행
    KImageGray img = _q_pFormFocused->ImageGray();
    KImageGray openedImg = img.Opening(_WHITE, kernelSize, neighborType);  // neighborType 추가

    // 결과를 새로운 ImageForm에 표시
    ImageForm* q_newForm = new ImageForm(openedImg, "Opening Result", this);
    _lImageForm.push_back(q_newForm);
    q_newForm->show();

    UpdateUI();
}


void MainFrame::on_pushClosing_clicked()
{
    if (!_q_pFormFocused)
        return;

    // 현재 활성화된 ImageForm의 이미지에 폐쇄 연산 수행
    KImageGray img = _q_pFormFocused->ImageGray();
    KImageGray closedImg = img.Closing(_WHITE, kernelSize, neighborType);  // neighborType 추가

    // 결과를 새로운 ImageForm에 표시
    ImageForm* q_newForm = new ImageForm(closedImg, "Closing Result", this);
    _lImageForm.push_back(q_newForm);
    q_newForm->show();

    UpdateUI();
}

bool isForeground = true;  // 기본값은 전경


void MainFrame::on_pushExtraction_clicked()
{
    if (!_q_pFormFocused)
        return;

    KImageGray img = _q_pFormFocused->ImageGray();
    KImageGray boundaryImg;

    if (isForeground) {
        // Extract boundary for white (foreground)
        boundaryImg = KImageGray::SubtractImages(img, img.BinaryErode(_WHITE, kernelSize, neighborType));
    } else {
        // Extract boundary for black (background) using dilation on the foreground
        boundaryImg = KImageGray::SubtractImages(img.BinaryDilate(_WHITE, kernelSize, neighborType), img);
    }

    // 결과를 새로운 ImageForm에 표시
    ImageForm* q_newForm = new ImageForm(boundaryImg, "Boundary Extraction", this);
    _lImageForm.push_back(q_newForm);
    q_newForm->show();

    UpdateUI();
}


void MainFrame::on_selectBackground_toggled(bool checked)
{
    if (checked) {
        isForeground = false;
    }
}

void MainFrame::on_selectForeground_toggled(bool checked)
{
    if (checked) {
        isForeground = true;
    }
}
