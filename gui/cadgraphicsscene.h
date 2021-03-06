#ifndef CADGRAPHICSSCENE_H
#define CADGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QXmlStreamWriter>
#include <QUndoStack>
#include <QMenu>
#include <QToolTip>

#include "qmath.h"
#include "cadcommands/cadcommandadd.h"
#include "cadcommands/cadcommanddelete.h"
#include "cadcommands/cadcommandmove.h"
#include "clipboardstack.h"

class CadGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit CadGraphicsScene(QObject *parent, QUndoStack *);
    enum Mode { NoMode, PointMode, LineMode, CircleMode, EllipseMode, TextMode,
                ArcMode, ImageMode, DeleteMode, DimHorizontalMode };

    void writeStream(QXmlStreamWriter *stream);
    void readStream(QXmlStreamReader *stream);
    void drawBackground(QPainter *painter, const QRectF &rect);
    void setFlags();
    void drawEntity(QGraphicsItem *item);
    bool eventFilter(QObject *watched, QEvent *event);
    qreal roundOff(qreal, qreal);
    QString setStatusBarMessage();

    typedef QPair<QGraphicsItem *, QPointF> entityPos;
    QList<entityPos> selectedEntities;
    QPointF startP, midP, endP, tempPoint;
    bool isInvertedSelection;
    bool isGridVisible;
    int id, contextItemId;
    QString imagePath;
    QString message;
    qreal snapTo;
    QPointF endPoint;
    QPointF centerPoint;
    bool endPointSnap;
    bool centerSnap;

public slots:
    void setMode(Mode mode);
    void selectItems();
    void selectDeselectAllItems(bool b);
    void invertSelection();
    void deleteItems();
    void editorLostFocus(Text *item);
    void cut(getEntity *);
    void copy(getEntity *);
    void paste(const QPointF &pos);
    void menuAction(QAction *);

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *mouseEvent);
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void areItemsSelectable(bool);

signals:
    void itemSelected(QGraphicsItem *item);
    void setSelectionSignal();
    void setMessage();

private:
    Mode entityMode;
    bool mFirstClick;
    bool mSecondClick;
    bool mThirdClick;
    bool mPaintFlag;
    qreal x, y, rad, radM, angle, dx, dy;
    QString str;
    QPen paintpen, linePen;
    QPointF contextPosition;
    QPointF lineEndPoint;
    QPointF lineStartPoint;
    float differenceX;
    float differenceY;
    QList<QPointF> endPointsList;
    QList<QPointF> centerPointsList;

    QList<QGraphicsItem *> itemList;
    QList<QGraphicsItem *> previewList;
    Point *pointItem;
    Line *lineItem;
    Line *horizontalAxis, *verticalAxis;
    Circle *circleItem;
    Ellipse *ellipseItem;
    Text *textItem;
    Arc *arcItem;
    Image *imageItem;
    DimHorizontal *dimHorizontalItem;
    QUndoStack *mUndoStack;
    QMenu *contextMenu;
    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;
    QGraphicsItem *contextItem;
    QGraphicsItem *clickedItem;
};

#endif // CADGRAPHICSSCENE_H
