#include <QTextStream>
#include <QMessageBox>
#include <QDateTime>
#include "solitaire.h"
#include "qgamehelpdlg.h"

Solitaire::Solitaire(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	connect(ui.graphicsView, SIGNAL(select_piece(QPoint)), this, SLOT(SelectPiece(QPoint)));
	connect(ui.graphicsView, SIGNAL(hover_blank(QPoint)), this, SLOT(HoverBlank(QPoint)));
	connect(ui.graphicsView, SIGNAL(down_piece(QPoint)), this, SLOT(DownPiece(QPoint)));
	connect(ui.action_restart, SIGNAL(triggered()), this, SLOT(StartNewGame()));
	connect(ui.action_english, SIGNAL(triggered()), this, SLOT(StartNewGame()));
	connect(ui.action_european, SIGNAL(triggered()), this, SLOT(StartNewGame()));
	connect(ui.action_finish, SIGNAL(triggered()), this, SLOT(FinishGame()));
	connect(ui.action_about, SIGNAL(triggered()), this, SLOT(ShowAbout()));
	connect(ui.action_help, SIGNAL(triggered()), this, SLOT(ShowHelp()));
	gameModes = new QActionGroup(this);
    gameModes->addAction(ui.action_english);
    gameModes->addAction(ui.action_european);
	StartNewGame();
}

Solitaire::~Solitaire()
{}

void Solitaire::SelectPiece(QPoint pos)
{
	if (isFinished)
	{
		return;
	}
	QPoint selPoint = getPiecePoint(pos);
	if (selPoint.x() >= 0 && selPoint.y() >= 0 && selPoint.x() < 7 && selPoint.y() < 7 && engine->GetBoardNum(selPoint.x(), selPoint.y()) == 1)
	{
		selectedPiece = new QPoint(selPoint.x(), selPoint.y());
		PaintBoard();
	}
	else
	{
		selectedPiece = new QPoint(-1, -1);
	}
}

void Solitaire::HoverBlank(QPoint pos)
{
	if (isFinished)
	{
		return;
	}
	QPoint hovPoint = getPiecePoint(pos);
	if (hovPoint.x() >= 0 && hovPoint.y() >= 0 && hovPoint.x() < 7 && hovPoint.y() < 7 && engine->GetBoardNum(hovPoint.x(), hovPoint.y()) == 0)
	{
		hoveredBlank = new QPoint(hovPoint.x(), hovPoint.y());
		PaintBoard();
	}
	else
	{
		hoveredBlank = new QPoint(-1, -1);
	}
}

void Solitaire::DownPiece(QPoint pos)
{
	if (isFinished)
	{
		return;
	}
	QPoint downPoint = getPiecePoint(pos);
	if (downPoint.x() >= 0 && downPoint.y() >= 0 && downPoint.x() < 7 && downPoint.y() < 7 && engine->GetBoardNum(downPoint.x(), downPoint.y()) == 0)
	{
		if (engine->MovePiece(selectedPiece->x(), selectedPiece->y(), downPoint.x(), downPoint.y()))
		{
			if (lastPoint != nullptr && lastPoint->x() == selectedPiece->x() && lastPoint->y() == selectedPiece->y())
			{
				if (recordingSteps)
				{
					if (!stepLogFile->open(QIODevice::WriteOnly | QIODevice::Append))
					{
						return;
					}
					QTextStream out(stepLogFile);
					out << " -> " << engine->GetSolName(downPoint.x(), downPoint.y());
					stepLogFile->close();
				}
			}
			else
			{
				moveSteps++;
				ui.statusBar->showMessage("Skip Count: " + QString("%1").arg(moveSteps));
				if (recordingSteps)
				{
					if (!stepLogFile->open(QIODevice::WriteOnly | QIODevice::Append))
					{
						return;
					}
					QTextStream out(stepLogFile);
					if (moveSteps > 1)
					{
						out << "\r\n";
					}
					out << "Step " << moveSteps << ":\r\n" << engine->GetSolName(selectedPiece->x(), selectedPiece->y()) << " -> " << engine->GetSolName(downPoint.x(), downPoint.y());
					stepLogFile->close();
				}
			}
			lastPoint = new QPoint(downPoint.x(), downPoint.y());
		}
	}
	selectedPiece = new QPoint(-1, -1);
	hoveredBlank = new QPoint(-1, -1);
	PaintBoard();
}

void Solitaire::resizeEvent(QResizeEvent* event)
{
    ui.graphicsView->setGeometry(0, 0, this->width(), this->height() - 56);
	PaintBoard();
}

void Solitaire::PaintBoard()
{
	if (engine != nullptr)
	{
		int minLength = this->width() <= this->height() - 56 ? this->width() : this->height() - 56;
		int pieceRoughSize = (minLength * 0.9) / 7;
		pieceSize = pieceRoughSize - pieceRoughSize % 10;
		leftStart = (this->width() - pieceSize * 7) / 2;
		topStart = (this->height() - 56 - pieceSize * 7) / 2;
		QGraphicsScene* scene = new QGraphicsScene(this);
		for (int y = 0; y < 7; y++)
		{
			for (int x = 0; x < 7; x++)
			{
				if (engine->GetBoardNum(x, y) == 1)
				{
					QPen pen;
					if (selectedPiece != nullptr && selectedPiece->x() >= 0 && selectedPiece->y() >= 0 && x == selectedPiece->x() && y == selectedPiece->y())
					{
						pen.setColor(Qt::red);
						pen.setWidth(2);
						pen.setStyle(Qt::SolidLine);
					}
					else
					{
						pen.setStyle(Qt::NoPen);
					}
					QRadialGradient radialGrad(QPointF(leftStart + pieceSize * x + pieceSize / 3, topStart + pieceSize * y + pieceSize / 3), pieceSize / 2);
					radialGrad.setColorAt(0, Qt::white);
					radialGrad.setColorAt(1, Qt::blue);
					QBrush brush(radialGrad);
					scene->addEllipse(QRectF(leftStart + pieceSize * x + 1, topStart + pieceSize * y + 1, pieceSize - 2, pieceSize - 2), pen, brush);
				}
				if (engine->GetBoardNum(x, y) == 0)
				{
					QPen pen;
					pen.setColor(Qt::black);
					pen.setWidth(1);
					QBrush brush;
					if (hoveredBlank != nullptr && hoveredBlank->x() >= 0 && hoveredBlank->y() >= 0 && x == hoveredBlank->x() && y == hoveredBlank->y())
					{
						brush.setColor(Qt::black);
						brush.setStyle(Qt::Dense5Pattern);
					}
					else
					{
						brush.setStyle(Qt::NoBrush);
					}
					scene->addEllipse(QRectF(leftStart + pieceSize * x + 1, topStart + pieceSize * y + 1, pieceSize - 2, pieceSize - 2), pen, brush);
				}
			}
		}
		ui.graphicsView->setScene(scene);
	}
}

QPoint Solitaire::getPiecePoint(QPoint pos)
{
	QPoint distPoint = pos - QPoint(leftStart, topStart);
	if (distPoint.x() >= 0 && distPoint.y() >= 0)
	{
		return QPoint(distPoint.x() / pieceSize, distPoint.y() / pieceSize);
	}
	else
	{
		return QPoint(-1, -1);
	}
}

void Solitaire::StartNewGame()
{
	int variant = ui.action_english->isChecked() ? 0 : 1;
	engine = new SolEngine();
	engine->StartNewBoard(variant);
	moveSteps = 0;
	ui.statusBar->showMessage("");
	isFinished = false;
	recordingSteps = ui.action_record->isChecked();
	PaintBoard();
	if (recordingSteps)
	{
		QDateTime nowTime = QDateTime::currentDateTime();
		QString filename = "SOL_" + nowTime.toString("yyyyMMddhhmmsszzz") + ".log";
		stepLogFile = new QFile(filename);
	}
}

void Solitaire::FinishGame()
{
	int leftPieceCount = engine->CheckLeftPieces();
	if (leftPieceCount > 1)
	{
		if (QMessageBox::question(this, QString(), "Are you sure?") == QMessageBox::No)
		{
			return;
		}
	}
	QMessageBox msgBox;
	if (leftPieceCount == -1)
	{
		msgBox.setText("A Genius (" + QString("%1").arg(moveSteps) + " skips)");
	}
	else if (leftPieceCount == 1)
	{
		msgBox.setText("Take A Deep Bow");
	}
	else if (leftPieceCount == 2)
	{
		msgBox.setText("A Sharpie");
	}
	else if (leftPieceCount == 3)
	{
		msgBox.setText("Really Clever");
	}
	else if (leftPieceCount == 4)
	{
		msgBox.setText("Better");
	}
	else if (leftPieceCount == 5)
	{
		msgBox.setText("Good");
	}
	else
	{
		msgBox.setText("GAME OVER");
	}
	msgBox.exec();
	isFinished = true;
}

void Solitaire::ShowAbout()
{
	QMessageBox::about(this, "About", "About Solitaire\r\n\r\nVersion 1.0\r\n2024.10.25");
}

void Solitaire::ShowHelp()
{
	QGameHelpDlg dlg;
	dlg.exec();
}
