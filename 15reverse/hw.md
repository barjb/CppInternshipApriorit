# Homework
## Cracking
1. Firstly I execute file, type random serial number and click check. Wrong! message pops up.
2. Then I'm checking hardcoded strings in IDA using Shift+F12. "Right!" and "Wrong!" are listed. It seems like there isn't any string connected to serial numbers generator. Both strings are located in DialogFunc function.
3. Looking into "start" function there are calls to GetModuleHandleA and DialogBoxParamA. Then it finishes program executrion. 
GetModuleHandleA is called with 0 as argument so it returns handle to the file used to create the calling process (.exe file).
DialogBoxParamA uses DialogFunc as a dialog box procedure so we should debug it to crack the serial number.
4. I start the debugging process. I see call to GetDlgItemTextA, which retrieves the title or text associated with a control in a dialog box.
5. In the next line password lenght is pushed to eax, if lenght is 6, ZF is set so we jump to "loc_401076"
6. Then password is passed as an argument to sub_4010D6.
7. After call returns we compare eax to 1, if eax is 1, then we get message Right!. So we should find password which will set eax to 1 on sub_4010D6 exit.
8. I look into "sub_4010D6" in graph view. There is one box setting eax to 1 on exit.
9. Then loop is executed password lenght number of times (always exacly 6 times). It gets ASCII value of each character adds 10h, index, and then increments index.
```text
.text:004010E4 xor     eax, eax
.text:004010E6 mov     al, [ecx+esi]
.text:004010E9 add     al, 10h
.text:004010EB add     eax, ecx
.text:004010ED add     edi, eax
.text:004010EF inc     ecx
```
10. Then accumulated result should be equal to 2F2h. If it isn't eax is set to 0 and we leave. So it's wrong path. Ex password matching 2F2h: helloo
11. Last character is added to the sum.
```text
.text:004010FD mov     al, [esi]
.text:004010FF add     al, [esi+5]
.text:00401102 cmp     al, 0DEh
```
Sum should be ODEh. So last character should be carefully selected. Password helloo doesn't work anymore.
12. Last step
```text
.text:00401106 mov     al, [esi+2]
.text:00401109 add     al, [esi+3]
.text:0040110C cmp     al, 0D4h
```
We move third character to register, add fourth and their sum should be equal to OD4h

13. Dial box Right! Is presented to the user!

## Algorithm
1. Serial has 6 characters length
2. Serial passes points 9-12.

## Generator + cracked program
Due to the internet connection problems I couldn't finish all 3 tasks on time.