clear all ;
close all;

M=dlmread('CAPTURE5.TXT')
t=0:1499;
t=t*0.004;
comm=[zeros(1,500) ones(1,500),-ones(1,500)]';
Pos=M(1:1500);
Vit=M(1501:3000);
Vit=Vit+20;
figure
subplot(211);
plot(t,Vit,'k');hold on;
plot(t,comm*600);
subplot(212);
plot(t,Pos,'r');


