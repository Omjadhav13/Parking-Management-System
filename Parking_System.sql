create database Parking_System;
use parking_System;

create table Vehicles(
vehicleNo VARCHAR(20) PRIMARY KEY,
ownerName VARCHAR(50) NOT NULL,
entryTime DATETIME NOT NULL,
exitTime DATETIME,
status ENUM('Parked', 'Exited') DEFAULT 'Parked');

CREATE TABLE ParkingSlots (
    slotId INT PRIMARY KEY AUTO_INCREMENT,
    status ENUM('Free', 'Occupied') DEFAULT 'Free'
);

INSERT INTO Vehicles (vehicleNo, ownerName, entryTime, status)
VALUES ('MH12AB1234', 'Om', NOW(), 'Parked');

select * from Vehicles;

UPDATE Vehicles
SET exitTime = NOW(), status = 'Exited'
WHERE vehicleNo = 'MH12AB1234' AND status = 'Parked';

SELECT vehicleNo, ownerName, entryTime
FROM Vehicles
WHERE status = 'Parked';

SELECT slotId
FROM ParkingSlots
WHERE status = 'Free';

SELECT vehicleNo,
       ownerName,
       entryTime,
       exitTime,
       TIMESTAMPDIFF(MINUTE, entryTime, exitTime) AS duration_minutes,
       (TIMESTAMPDIFF(MINUTE, entryTime, exitTime) * 20) AS charges  -- Example Rs.2/min
FROM Vehicles
WHERE status = 'Exited';

SELECT * FROM Vehicles
WHERE vehicleNo = 'MH12AB1234' AND status = 'Parked';

DELETE FROM Vehicles
WHERE vehicleNo = 'MH12AB1234';	




