#pragma once

#include <QPlainTextEdit>
#include <QKeyEvent>
#include <QDebug>

class TextUpdate : public QPlainTextEdit
{
	Q_OBJECT

public:
	TextUpdate(QWidget *parent = 0) : QPlainTextEdit(parent)
	{
	}

protected:
	virtual void keyPressEvent(QKeyEvent *event) {

		if( event->key() == Qt::Key_Return && event->modifiers() == Qt::ShiftModifier )
		{
			emit submit();
		} else if( event->key() == Qt::Key_Escape ) {
			emit cancel();
		}

		QPlainTextEdit::keyPressEvent(event);
	}

signals:
	void submit();
	void cancel();
};
