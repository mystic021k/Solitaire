#pragma once
#include <QtWidgets/QMainWindow>
#include <QFile>
#include "ui_solitaire.h"
#include "solEngine.h"

class Solitaire : public QMainWindow
{
    Q_OBJECT

public:
    Solitaire(QWidget *parent = nullptr);
    ~Solitaire();

    void resizeEvent(QResizeEvent* event);

private:
    Ui::SolitaireClass ui;
    QActionGroup* gameModes;
    SolEngine* engine;
    int pieceSize;
    int leftStart;
    int topStart;
    QPoint* selectedPiece;
    QPoint* hoveredBlank;
    QPoint* lastPoint;
    QFile* stepLogFile;
    int gameVariant = 0;
    int moveSteps = 0;
    bool isFinished = false;
    bool recordingSteps = false;
    void PaintBoard();
    QPoint getPiecePoint(QPoint pos);

public slots:
    void SelectPiece(QPoint pos);
    void HoverBlank(QPoint pos);
    void DownPiece(QPoint pos);
    void StartNewGame();
    void ChangeGame(QAction* action);
    void FinishGame();
    void ShowAbout();
    void ShowHelp();
};
