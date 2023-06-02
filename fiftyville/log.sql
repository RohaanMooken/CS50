-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Had to start somewhere so I started with the crime reports
-- ID: 295, 28.07.2021, Humphrey Street
-- TIME: 10.15 am
-- Three witnesses present
-- Mentions bakery
SELECT * FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28;

-- Hoping to find some useful information since bakery was mentioned, none yet
SELECT * FROM bakery_security_logs WHERE day = 28 AND month = 7 AND year = 2021;

-- Found very useful information from the interviews
-- IDs: 161, 162 and 163
-- Within 10 min of theft got into bakery parking and drove away
-- Thief withdrew money from atm before theft on Leggett Street
-- As he was leaving, called someone for less than a minute
-- Earliest flight out tomorrow/29.07
-- Accomplice bought ticket
SELECT * FROM interviews WHERE day = 28 AND month = 7 AND year = 2021;

-- didn't find anything useful yet, but maybe later
SELECT * FROM atm_transactions WHERE day = 28 AND month = 7
AND year = 2021 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';

-- No useful info yet
SELECT * FROM phone_calls
WHERE day = 28 AND month = 7 AND year = 2021 AND duration < 60;

-- Updated to add hour 10 because of earlier information
-- Shortened list of suspected license plates
SELECT * FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND year = 2021
AND hour = 10 AND minute > 15 AND minute < 25;

-- Found the flight they purchased based on earlier information
-- ID: 36
-- ORIGION airport: 8
-- Destination airport: 4
-- TIME: 08.20
SELECT * FROM flights WHERE day = 29 AND month = 7 AND year = 2021 ORDER BY hour ASC;

--                    id | abbreviation |          full_name          |     city
-- Theif coming from  8  | CSF          | Fiftyville Regional Airport | Fiftyville
-- Theif going to     4  | LGA          | LaGuardia Airport           | New York City
SELECT * FROM airports WHERE id = 4 OR id = 8;

-- Based on the flight id from earlier
-- Found passport nums and seats
SELECT * FROM passengers WHERE flight_id = 36;

-- Found list of people on the flight with all their info
SELECT * FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
WHERE passengers.flight_id = 36;

-- Found four possible suspect with crossreferencing their license plates
--    id   |  name  |  phone_number  | passport_number | license_plate | flight_id | passport_number | seat |
+--------+--------+----------------+-----------------+---------------+-----------+-----------------+------+
--| 398010 | Sofia  | (130) 555-0289 | 1695452385      | G412CB7       | 36        | 1695452385      | 3B   |
--| 686048 | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       | 36        | 5773159633      | 4A   |
--| 560886 | Kelsey | (499) 555-9472 | 8294398571      | 0NTHK55       | 36        | 8294398571      | 6C   |
--| 467400 | Luca   | (389) 555-5198 | 8496433585      | 4328GD8       | 36        | 8496433585      | 7B
SELECT * FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
WHERE passengers.flight_id = 36 AND license_plate IN(
    SELECT license_plate FROM bakery_security_logs
    WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 AND
    minute > 15 AND minute < 25);

-- Narrowed down to 2 bank accounts
--  account_number | person_id | creation_year |
--+----------------+-----------+---------------+
--| 49610011       | 686048    | 2010          |
--| 28500762       | 467400    | 2014
SELECT * FROM bank_accounts
WHERE person_id IN(
    SELECT id FROM people
    JOIN passengers ON passengers.passport_number = people.passport_number
    WHERE passengers.flight_id = 36 AND license_plate IN(
        SELECT license_plate FROM bakery_security_logs
        WHERE day = 28 AND month = 7 AND year = 2021
        AND hour = 10 AND minute > 15 AND minute < 25));

-- Thought I could find the suspect but two were given back the same as above
--  id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
--+-----+----------------+------+-------+-----+----------------+------------------+--------+
--| 246 | 28500762       | 2021 | 7     | 28  | Leggett Street | withdraw         | 48     |
--| 267 | 49610011       | 2021 | 7     | 28  | Leggett Street | withdraw         | 50
SELECT * FROM atm_transactions WHERE day = 28 AND month = 7
AND year = 2021 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'
AND account_number IN(SELECT account_number FROM bank_accounts
WHERE person_id IN(
    SELECT id FROM people
    JOIN passengers ON passengers.passport_number = people.passport_number
    WHERE passengers.flight_id = 36 AND license_plate IN(
        SELECT license_plate FROM bakery_security_logs
        WHERE day = 28 AND month = 7 AND year = 2021
        AND hour = 10 AND minute > 15 AND minute < 25)));

-- Shortened list of suspects to four callers
SELECT * FROM phone_calls
WHERE day = 28 AND month = 7 AND year = 2021 AND duration < 60 AND caller IN (SELECT phone_number FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
WHERE passengers.flight_id = 36 AND license_plate IN(
    SELECT license_plate FROM bakery_security_logs
    WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 AND
    minute > 15 AND minute < 25));

-- Shortened to three people
SELECT id FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
WHERE passengers.flight_id = 36 AND license_plate IN(
    SELECT license_plate FROM bakery_security_logs
    WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 AND
    minute > 15 AND minute < 25) AND phone_number IN(
        SELECT caller FROM phone_calls
        WHERE day = 28 AND month = 7 AND year = 2021 AND duration < 60 AND caller IN(
            SELECT phone_number FROM people
            JOIN passengers ON passengers.passport_number = people.passport_number
            WHERE passengers.flight_id = 36 AND license_plate IN(
                SELECT license_plate FROM bakery_security_logs
                WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 AND
                minute > 15 AND minute < 25)));

-- Found one possible suspect
--  account_number | person_id | creation_year |
--+----------------+-----------+---------------+
--| 49610011       | 686048    | 2010
SELECT * FROM bank_accounts
WHERE person_id IN(
    SELECT id FROM people
    JOIN passengers ON passengers.passport_number = people.passport_number
    WHERE passengers.flight_id = 36 AND license_plate IN(
        SELECT license_plate FROM bakery_security_logs
        WHERE day = 28 AND month = 7 AND year = 2021
        AND hour = 10 AND minute > 15 AND minute < 25)) AND person_id IN(
            SELECT id FROM people
            JOIN passengers ON passengers.passport_number = people.passport_number
            WHERE passengers.flight_id = 36 AND license_plate IN(
                SELECT license_plate FROM bakery_security_logs
                WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 AND
                minute > 15 AND minute < 25) AND phone_number IN(
                    SELECT caller FROM phone_calls
                    WHERE day = 28 AND month = 7 AND year = 2021 AND duration < 60 AND caller IN(
                        SELECT phone_number FROM people
                        JOIN passengers ON passengers.passport_number = people.passport_number
                        WHERE passengers.flight_id = 36 AND license_plate IN(
                            SELECT license_plate FROM bakery_security_logs
                            WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 AND
                            minute > 15 AND minute < 25))));

-- Thief is Bruce
--    id   | name  |  phone_number  | passport_number | license_plate |
--+--------+-------+----------------+-----------------+---------------+
--| 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X
SELECT * FROM people WHERE id = 686048;

-- Double check with license plates from bakery
SELECT * FROM people WHERE id = 686048 AND license_plate IN(
    SELECT license_plate FROM bakery_security_logs
    WHERE day = 28 AND month = 7 AND year = 2021
    AND hour = 10 AND minute > 15 AND minute < 25);

-- Found Bruce and accomplic's phone call
SELECT * FROM phone_calls
WHERE day = 28 AND month = 7 AND year = 2021 AND duration < 60 AND caller IN(
    SELECT phone_number FROM people WHERE id = 686048 AND license_plate IN(
    SELECT license_plate FROM bakery_security_logs
    WHERE day = 28 AND month = 7 AND year = 2021
    AND hour = 10 AND minute > 15 AND minute < 25));

-- Found Accomplic - Robin
--    id   | name  |  phone_number  | passport_number | license_plate |
--+--------+-------+----------------+-----------------+---------------+
--| 864400 | Robin | (375) 555-8161 |                 | 4V16VO0       |
--+--------+-------+----------------+-----------------+----------
SELECT * FROM people WHERE phone_number In(
    SELECT receiver FROM phone_calls
    WHERE day = 28 AND month = 7 AND year = 2021 AND duration < 60 AND caller IN(
        SELECT phone_number FROM people WHERE id = 686048 AND license_plate IN(
            SELECT license_plate FROM bakery_security_logs
            WHERE day = 28 AND month = 7 AND year = 2021
            AND hour = 10 AND minute > 15 AND minute < 25)));