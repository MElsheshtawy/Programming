The Results of task A:
the minimum speed in MPH = 0.301485
the maximum speed in MPH= 48.8247
the Power using integraion in kWh= 0.300666

comment: the speed is okay but the power used is to low I expected it to be more so I guess their is a problem in the integration because of the cells that contained zero in ampere and a number in voltage and vice versa

shortly: I know how to solve it but it will take to much time to handle it because I will have to take the average of readings for voltage and ampere in fixed time intervals (digitalize the readings somehow)

The Results of task B:
the minimum speed in MPH = 0.66182
the maximum speed in MPH= 93.5596
the average speed in MPH= 28.3464
the Power using integraion in kWh= 84.0808

Comment: All the answers are pretty normal and the integration worked because I tried other technique which wasn't dependent on the time that much but it has some errors and in order to solve it I will need to draw my function as digital pulses as I said in the comment in task A

The Results of Task C:
answer: the float number I put in the encoder appears on the decoder

Comment: I could have made the decoder more universal and decode characters and strings too but I ran out of time and I had some circumstances that I would have no problem to elaborate on 


How to use or run my tasks?
Part A & B: just put the path of the file and click run but wait a bit because the files is a bit long and the time complexity of the code isn't the best I could have made it faster but I would have used more memory and I didn't know which one is favoured
Part C: Create a file and put its path and choose a number you want to encode then run the two file encoder then decoder


optional part?
1- The tasks was easy. The hard part was that I had to do all of them in 6 hours only because I had a problem in one of my courses that I had to finish 26 hours of lectures before I can understand any thing and also assignments (I was unlucky this week)

2- a) the time was a con to be honest you could have made an internal timer or something to start from zero and just increament this number by one each second this would have saved memory and also been easier in parsing
b) the data in part B could have been sent as hexa all of it with each byte having specific role
c) the log format was so clean and you can understand it and code a parser for it without much assistance (wasn't cyphered)

3- my parser has linear complexity O(characters+lines) characters>>lines so O(characters)
I could have decreased it a bit by neglecting more lines using some knowledge about the data but that would have made the could uglier which isn't good because I have to explain it in design review :)

4- I will send it in an email if I had time to make it :)

5- Loss of Traction or Control => this might cause the rear wheel to move so fast and the front wheel not (accelerating so fast)

6- I didn't deal with it but yeah their was a better way that would have consumed more memory which is to make a unordered map that has its key as the time and pointing to a pair then assign your numbers in this unordered map then store this map in a vector while filtering all the data that doesn't have a pair or just take average for the data missing by the knowledge of the data after and before it in time

7- it is O(bytes) and I really don't know because I am not experienced with encoders and decoders

