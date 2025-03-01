-- Keep a log of any SQL queries you execute as you solve the mystery.
-- see all of the available tables
.tables
-- see the properties of the crime_scene_reports table
.schema crime_scene_reports
-- determine the ids of the culprits
SELECT id FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street";
-- determine what information can be accessed from each table, so that the id can be used to find information about the culprits
.schema airports
.schema people
.schema atm_transactions
.schema flights
.schema phone_calls
.schema bakery_security_logs
.schema interviews
.schema bank_accounts
.schema passengers
-- determine who did the crime
SELECT description  FROM crime_scene_reports WHERE id = 297;
    -- Littering took place at 16:36. No known witnesses.
SELECT description  FROM crime_scene_reports WHERE id = 295;
    -- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
    -- Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
SELECT transcript FROM interviews WHERE year = 2021 AND month = 7 AND day = 28 AND transcript like "%bakery%";
-- | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
-- | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
-- | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |
SELECT city FROM airports JOIN flights ON flights.destination_airport_id = airports.id WHERE flights.year = 2021 AND flights.month = 7 AND flights.day = 29 AND flights.origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville") ORDER BY hour, minute;
-- determine the earliest flight (NYC)
-- Determine the 2 people
SELECT name FROM people WHERE people.phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60) AND people.passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE year = 2021 AND month = 7 AND day = 29 ORDER BY hour,minute LIMIT 1)) AND people.license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 10 AND minute <= 20) AND people.id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location = "Leggett Street" AND year = 2021 AND month = 7 AND day = 28 AND transaction_type  = "withdraw"));
SELECT name FROM people WHERE people.phone_number IN (SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 AND caller = (SELECT phone_number FROM people WHERE name = "Bruce"));