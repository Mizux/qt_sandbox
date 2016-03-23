//! @file
#pragma once

#include <QGraphicsObject>
#include <QFont>
#include <QBrush>
#include <QPen>

class TextItem : public QGraphicsObject {
	public:
	TextItem(const QString& text, QGraphicsItem* parent = 0);
	virtual ~TextItem() = default;

	QString text() const;
	void setText(const QString& text);

	QFont font() const;
	void setFont(const QFont& font);

	QBrush brush() const;
	void setBrush(const QBrush& brush);

	QPen pen() const;
	void setPen(const QPen& pen);

	QSizeF size() const;
	QRectF boundingRect() const override;
	void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override;

	protected:
	QString _text;
	QFont _font;
	QBrush _brush;
	QPen _pen;
};
