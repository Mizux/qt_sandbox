# qt_sandbox
Some test of Qt Features

## Animation
The aims of this test, is try to reproduce Drag 'n Drop action like in *Pokemon Shuffle (tm)*.  
In a *QGraphicView* using *Tile* class as grid slot and *Item* class as pokemon entity.

- I want to be able to move Item from a grid slot (i.e. Tile) to an other one.
- I want to have some "tile" which didn't allow drop.
- When I drag over potential drop site, I want a feedback (tile paint).
- During the drag, item "change" its aspect and the cursor become the "Item".
- If the Drag is cancel, "Item" return its previous position (i.e. cursor return to "hand" and item retrieve its aspect)
