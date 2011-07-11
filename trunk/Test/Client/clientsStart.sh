#!/bin/bash
{
client0/./client i.jpg &
client1/./client l.jpg &
client2/./client j.jpg &
client3/./client s.jpg &
client4/./client tux.jpg &
wait
}
