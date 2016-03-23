//! @file

#include "text_item.hpp"

#include <QPainter>
#include <iostream>

TextItem::TextItem(const QString& text, QGraphicsItem* parent)
  : QGraphicsObject(parent)
  , _text()
  , _font()
  , _brush()
  , _pen() {
	_text = text;

	_font = QFont();
	_font.setStyleHint(QFont::Monospace, QFont::ForceOutline);
	_font.setFamily("DejaVu Sans Mono");
	_font.setPointSizeF(48.0);

	QFontMetrics fm(_font);
	QLinearGradient linearGrad(QPointF(0, fm.descent()),
	                           QPointF(0, -fm.ascent()));
	linearGrad.setColorAt(0, Qt::red);
	linearGrad.setColorAt(1, Qt::yellow);

	_brush = QBrush(linearGrad);

	_pen = QPen(QColor(255, 255, 255));
	_pen.setWidth(1);
}

QString
TextItem::text() const {
	return _text;
}

void
TextItem::setText(const QString& text) {
	_text = text;
}

QFont
TextItem::font() const {
	return _font;
}

void
TextItem::setFont(const QFont& font) {
	_font = font;
}

QBrush
TextItem::brush() const {
	return _brush;
}

void
TextItem::setBrush(const QBrush& brush) {
	_brush = brush;
}

QPen
TextItem::pen() const {
	return _pen;
}

void
TextItem::setPen(const QPen& pen) {
	_pen = pen;
}

QSizeF
TextItem::size() const {
	QFontMetrics fm(_font);
	int width  = fm.width(_text);
	int height = fm.height();

	return QSizeF(width, height);
}

QRectF
TextItem::boundingRect() const {
	QFontMetrics fm(_font);
	return QRectF(QPointF(0, (fm.descent() + 0.5) / fm.height()),
	              QPointF((fm.width(_text) + 0.5) / fm.height(),
	                      -(fm.ascent() + 0.5) / fm.height()));
}

void
TextItem::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
	painter->setRenderHint(QPainter::Antialiasing);
	painter->setFont(_font);
	painter->setBrush(_brush);
	painter->setPen(_pen);

	QFontMetrics fm(_font);
	painter->scale(1.0 / fm.height(), 1.0 / fm.height());

	QPainterPath path;
	path.addText(QPointF(0, 0), _font, _text);
	painter->drawPath(path);
}
