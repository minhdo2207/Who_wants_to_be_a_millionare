#ifndef HISTORY_SCORE_H
#define HISTORY_SCORE_H

#include <QDialog>

namespace Ui {
class history_score;
}

class history_score : public QDialog
{
    Q_OBJECT

public:
    explicit history_score(QWidget *parent = nullptr);
    ~history_score();

private:
    Ui::history_score *ui;
};

#endif // HISTORY_SCORE_H
