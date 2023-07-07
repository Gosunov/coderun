WITH RECURSIVE getParent AS (
  SELECT track_id, track_genre.genre_id genre_id from track_genre
  UNION ALL
  SELECT getParent.track_id, parent_genre_id FROM getParent, genre 
  WHERE getParent.genre_id=genre.id and parent_genre_id IS not NULL
) 
SELECT DISTINCT track_id, genre_id, track.name, genre.name FROM getParent 
JOIN track ON track.id=track_id
JOIN genre On genre.id=genre_id 
ORDER By track_id, genre_id
