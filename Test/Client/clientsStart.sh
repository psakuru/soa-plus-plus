#!/bin/bash
{
cd client0
./client i.jpg &
cd ../client1
./client l.jpg &
cd ../client2
./client j.jpg &
cd ../client3
./client s.jpg &
cd ../client4
./client tux.jpg &
wait
}
