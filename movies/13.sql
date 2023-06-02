-- SELECT DISTINCT(name) FROM people JOIN stars ON stars.person_id = id WHERE name = 'Kevin Bacon' AND birth = 1958;

SELECT DISTINCT(name) FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies ON stars.movie_id = movies.id
WHERE movies.title IN(
SELECT DISTINCT(movies.title) FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies ON stars.movie_id = movies.id
WHERE people.name = 'Kevin Bacon' AND people.birth = 1958) AND people.name != 'Kevin Bacon';