SELECT id FROM Points point 
WHERE 
point(point.x, point.y) <@ box'((_X_LEFT_,_Y_TOP_),(_X_RIGHT_,_Y_BOTTOM_))'
UNION
SELECT id FROM Lines line
WHERE 
lseg(point(line.begin_x,line.begin_y),point(line.end_x,line.end_y)) <@ box'((_X_LEFT_,_Y_TOP_),(_X_RIGHT_,_Y_BOTTOM_))'
OR
lseg(point(line.begin_x,line.begin_y),point(line.end_x,line.end_y)) ?# box'((_X_LEFT_,_Y_TOP_),(_X_RIGHT_,_Y_BOTTOM_))'
UNION
SELECT DISTINCT id FROM Polygons poly
WHERE 
lseg(point(poly.begin_x,poly.begin_y),point(poly.end_x,poly.end_y)) <@ box'((_X_LEFT_,_Y_TOP_),(_X_RIGHT_,_Y_BOTTOM_))'
OR
lseg(point(poly.begin_x,poly.begin_y),point(poly.end_x,poly.end_y)) ?# box'((_X_LEFT_,_Y_TOP_),(_X_RIGHT_,_Y_BOTTOM_))';