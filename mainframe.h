#ifndef MAINFRAME_H
#define MAINFRAME_H
#include "kfc.h"
#include <QDialog>

namespace Ui {
class MainFrame;

}

class ImageForm;

class MainFrame : public QDialog
{
    Q_OBJECT

private:
    Ui::MainFrame *ui;

    std::vector<ImageForm*>  _lImageForm;
    ImageForm*               _q_pFormFocused;

public:
    explicit MainFrame(QWidget *parent = 0);
    ~MainFrame();

    void    ImageFormFocused(ImageForm* q_pImageForm)
            {   _q_pFormFocused  = q_pImageForm;   //활성화된 창의 포인터를 저장함
                UpdateUI();                        //UI 활성화 갱신
            }
    void    UpdateUI();
    void    CloseImageForm(ImageForm* pForm);

public:
    void    focusInEvent(QFocusEvent *event);
    void    OnMousePos(const int& nX, const int& nY, ImageForm* q_pForm);
    void DisplayLabeledImage(const KImageGray& labeledImage);
    void UpdateLabelCountInView(int count);


private slots:
    void on_buttonOpen_clicked();
    void on_buttonDeleteContents_clicked();        
    void on_tabWidget_currentChanged(int index);               
    void on_buttonShowList_clicked();


    void on_select3by3_toggled(bool checked);

    void on_select5by5_toggled(bool checked);

    void on_select4N_toggled(bool checked);

    void on_select8N_toggled(bool checked);

    void on_pushOpening_clicked();

    void on_pushClosing_clicked();

    void on_pushExtraction_clicked();

    void on_selectBackground_toggled(bool checked);

    void on_selectForeground_toggled(bool checked);

protected:
    void closeEvent(QCloseEvent* event);
};

#endif // MAINFRAME_H
