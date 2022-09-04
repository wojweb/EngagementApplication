#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QEvent>

namespace Ui {
class graphWindow;
}

class GraphWindow : public QMainWindow
{
    Q_OBJECT

    QWidget* firstWindow;
public:
    explicit GraphWindow(int numOfUsers, QWidget *firstWindow, QWidget *parent = nullptr);
    ~GraphWindow();

private:
    Ui::graphWindow *ui;
//    void keyPressedEvent(QKeyEvent *key) override;
private slots:
    void backButtonClicked();

};

#endif // GRAPHWINDOW_H
