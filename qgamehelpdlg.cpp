#include "qgamehelpdlg.h"

QGameHelpDlg::QGameHelpDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	QString newline = "<br>";
	QString pStart = "<p>";
	QString pEnd = "</p>";
	QString spanStart = "<span>";
	QString spanEnd = "</span>";
	ui.textBrowser->setHtml(
		pStart + "The standard game fills the entire board with pegs except for the central hole. The objective is, making valid moves, to empty the entire board except for a solitary peg in the central hole." + pEnd
		+ pStart + "A valid move is to jump a peg orthogonally over an adjacent peg into a hole two positions away and then to remove the jumped peg." + pEnd
		+ pStart + "There are two traditional boards:"
		+ spanStart + newline + newline + "English:" + newline + "<img src=\":/icon/gif/board_english.gif\">" + newline + spanEnd
		+ spanStart + newline + newline + "European:" + newline + "<img src=\":/icon/gif/board_european.gif\">" + newline + spanEnd
		+ pEnd
	);
}

QGameHelpDlg::~QGameHelpDlg()
{}

void QGameHelpDlg::resizeEvent(QResizeEvent* event)
{
	ui.textBrowser->setGeometry(0, 0, this->width(), this->height());
}