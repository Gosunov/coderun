SELECT CAST ((SELECT EXTRACT(EPOCH FROM (SELECT SUM(r2.datetime - r1.datetime + r4.datetime - r3.datetime)
FROM requests r1 
LEFT JOIN requests r2 ON r2.host=r1.data AND r2.parent_request_id=r1.request_id
LEFT JOIN requests r3 ON r3.request_id=r2.request_id AND r3.parent_request_id=r1.request_id
LEFT JOIN requests r4 ON r4.request_id=r1.request_id AND split_part(r4.data, '	', 1)=r2.host
WHERE 
r1.type='RequestSent' 
AND 
r2.type='RequestReceived' 
AND 
r3.type='ResponseSent'
AND
r4.type='ResponseReceived'
))*1000) / (SELECT COUNT(DISTINCT r.request_id) FROM requests r WHERE r.parent_request_id ISNULL) aS NUMERIC) avg_network_time_ms