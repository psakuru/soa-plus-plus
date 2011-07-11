#!/bin/bash
{
cd client0
./client i.jpg 127.0.0.1:4000 &
cd ../client1
./client l.jpg 127.0.0.1:4000 &
cd ../client2
./client j.jpg 127.0.0.1:4000 &
cd ../client3
./client s.jpg 127.0.0.1:4000 &
cd ../client4
./client tux.jpg 127.0.0.1:4000 &
wait
}
