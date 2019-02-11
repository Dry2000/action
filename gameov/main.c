
#include <stdio.h>
#include <GLUT/glut.h>
#include<glpng/glpng.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<sys/time.h>
#include<string.h>
void Display(void);
void Reshape(int, int);
void Timer(int);
void SpecialKey(int,int,int);
void KeyBoard(unsigned char,int,int);
void PutSprite(int, int, int, pngInfo *);
void mouse(int,int,int,int);
//void Motion(int,int);
struct status{
    int posx;
    int posy;
    int inform;
    int jumpin;
    int fly;
    int dead;
    int fall;
    int firstposx;
    int firstposy;
    int damage;
    int wound;
    int jumping;
};
struct status enemies[1000];
GLuint img[100];
pngInfo info[100];

#define ON 1;
#define OFF 2;
int q[20][20],a,c,b,d,w,x,y,z,i,j,count,timer,nowt,map[1000][100],trush[32][32],counter,playe[2]={33,32*18};
int score,now,enemy,flying,prev,run,jumping,fall=0,reborn=3,previous[100][100],arms,bullet,bulletpos[2],burst,falling,stage=0,strain,jumpng;
char scores[10000],timess[100],zanki[100],inf[1000][21];
FILE *fp;
int main(int argc, char **argv){
    srandom((unsigned int)time(NULL));
    glutInit(&argc, argv);
    glutInitWindowSize(32*20,32*20);
    glutCreateWindow("PLAING GAME!!");
    glutKeyboardFunc(KeyBoard);
    glutSpecialFunc(SpecialKey);
    //glutMotionFunc(Motion);
    glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA |GLUT_DOUBLE);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutMouseFunc(mouse);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    img[1]=pngBind("glass.png", PNG_NOMIPMAP, PNG_ALPHA, &info[1], GL_CLAMP, GL_NEAREST, GL_NEAREST);
    img[2]=pngBind("block.png", PNG_NOMIPMAP, PNG_ALPHA, &info[2], GL_CLAMP, GL_NEAREST, GL_NEAREST);
    img[3]=pngBind("treasure.png", PNG_NOMIPMAP, PNG_ALPHA, &info[3], GL_CLAMP, GL_NEAREST, GL_NEAREST);
    img[4]=pngBind("bomb.png", PNG_NOMIPMAP, PNG_ALPHA, &info[4], GL_CLAMP, GL_NEAREST, GL_NEAREST);
    img[5]=pngBind("player.png", PNG_NOMIPMAP, PNG_ALPHA, &info[5], GL_CLAMP, GL_NEAREST, GL_NEAREST);
    img[6]=pngBind("title.png", PNG_NOMIPMAP, PNG_ALPHA, &info[6], GL_CLAMP, GL_NEAREST, GL_NEAREST);
    img[7]=pngBind("clear.png", PNG_NOMIPMAP, PNG_ALPHA, &info[7], GL_CLAMP, GL_NEAREST, GL_NEAREST);
    img[8]=pngBind("gameover.png", PNG_NOMIPMAP, PNG_ALPHA, &info[8], GL_CLAMP, GL_NEAREST, GL_NEAREST);
    img[9]=pngBind("warp.png", PNG_NOMIPMAP, PNG_ALPHA, &info[9], GL_CLAMP, GL_NEAREST, GL_NEAREST);
    img[10]=pngBind("enemy.png", PNG_NOMIPMAP, PNG_ALPHA, &info[10], GL_CLAMP, GL_NEAREST, GL_NEAREST);
    img[11]=pngBind("crow.png", PNG_NOMIPMAP, PNG_ALPHA, &info[11], GL_CLAMP, GL_NEAREST, GL_NEAREST);
    img[12]=pngBind("ninja.png", PNG_NOMIPMAP, PNG_ALPHA, &info[12], GL_CLAMP, GL_NEAREST, GL_NEAREST);
    img[13]=pngBind("bullet.png", PNG_NOMIPMAP, PNG_ALPHA, &info[13], GL_CLAMP, GL_NEAREST, GL_NEAREST);
    img[14]=pngBind("gun.png", PNG_NOMIPMAP, PNG_ALPHA, &info[14], GL_CLAMP, GL_NEAREST, GL_NEAREST);
    img[15]=pngBind("continue.png", PNG_NOMIPMAP, PNG_ALPHA, &info[15], GL_CLAMP, GL_NEAREST, GL_NEAREST);
    img[16]=pngBind("sword.png", PNG_NOMIPMAP, PNG_ALPHA, &info[16], GL_CLAMP, GL_NEAREST, GL_NEAREST);
    img[17]=pngBind("explain.png", PNG_NOMIPMAP, PNG_ALPHA, &info[17], GL_CLAMP, GL_NEAREST, GL_NEAREST);
    img[18]=pngBind("thaend.png", PNG_NOMIPMAP, PNG_ALPHA, &info[18], GL_CLAMP, GL_NEAREST, GL_NEAREST);
    
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutTimerFunc(1, Timer, 0);
    
    glutMainLoop();
    
    return 0;
    
}

void Reshape(int w, int h){
    glViewport(0,0,w,h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glScaled(1, -1, 1);
    glTranslated(0, -h, 0);
}

void Display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    if(now==0){
     //   printf("a\n");
        PutSprite(img[6], 0, 0, &info[6]);
        nowt=100;timer=0;
    }
    if(now==2){
        flying=0;
        jumping=16;
        fall=0;
        PutSprite(img[7], 0, 0, &info[7]);
        nowt=100;timer=0;
    }
    if(now==3){
                PutSprite(img[8], 0, 0, &info[8]);
        nowt=100;timer=0;
    }
    if(now==4){
        PutSprite(img[15], 0, 0, &info[15]);
        nowt=100;timer=0;
    }
    if(now==5){
        PutSprite(img[17], 0, 0, &info[17]);
        nowt=100;timer=0;
      //  printf("b\n");
    }
    if(now==7){
        PutSprite(img[18], 0, 0, &info[18]);
        nowt=100;timer=0;
        //  printf("b\n");
    }
    if(now==1||now==9){
        if(count==0){
            if(now==1){ enemy=0;
            if(stage==0){
                fp=fopen("map.txt","r");}
            if(stage==1){
                fp=fopen("map2.txt","r");}
            if(stage==2){
                fp=fopen("map3.txt","r");}
            if(stage==3){
                fp=fopen("map4.txt","r");}
            if(stage==4){
                fp=fopen("map5.txt","r");}
            for(i=0;i<100;i++){
                for(j=0;j<21;j++){
                    inf[i][j]=fgetc(fp);
                    if(inf[i][j-1]=='\n'){
                        inf[i][j-1]=inf[i][j];
                        j--;
                    }
                }
            }
            for(i=0;i<100;i++){
                for(j=0;j<21;j++){
                    switch(inf[i][j]){
                        case 'G':
                            map[i][j]=0;
                            continue;
                        case 'W':
                            map[i][j]=1;
                            continue;
                        case 'T':
                            map[i][j]=2;
                            continue;
                        case 'B':
                            map[i][j]=3;
                            continue;
                        case 'R':
                            map[i][j]=4;
                            continue;
                        case 'P':
                            map[i][j]=9;
                            continue;
                        case 'E':
                            map[i][j]=0;
                            enemies[enemy].firstposx=i*32;
                            enemies[enemy].firstposy=j*32;
                            enemies[enemy].posx=i*32;
                            enemies[enemy].posy=j*32;
                            enemies[enemy].inform=0;
                            enemy++;
                            continue;
                        case 'J':
                            map[i][j]=0;
                            enemies[enemy].firstposx=i*32;
                            enemies[enemy].firstposy=j*32;
                            enemies[enemy].posx=i*32;
                            enemies[enemy].posy=j*32;
                            enemies[enemy].inform=1;
                            enemy++;
                            continue;
                        case 'F':
                            map[i][j]=0;
                            enemies[enemy].firstposx=i*32;
                            enemies[enemy].firstposy=j*32;
                            enemies[enemy].posx=i*32;
                            enemies[enemy].posy=j*32;
                            enemies[enemy].inform=2;
                            enemy++;
                            continue;
                        case 'N':
                            map[i][j]=0;
                            enemies[enemy].posx=i*32;
                            enemies[enemy].posy=j*32;
                            enemies[enemy].firstposx=i*32;
                            enemies[enemy].firstposy=j*32;
                            enemies[enemy].inform=3;
                            enemy++;
                            continue;
                            
                    }
                }
            }
            }
            if(now==9){
        enemy=(int)3+8*random()/RAND_MAX;
            for(i=0;i<100;i++){
                for(j=0;j<100;j++){
                    if((i==1&&j==0)||(i==18&&j==19)){
                        map[i][j]=5;continue;
                    }
                    if(i==0 ||j==0||j==19){
                        map[i][j]=1;
                        continue;
                    }
                    if(i==18){
                        map[i][j]=9;continue;
                    }
                    
                        map[i][j]=0;
                    
                }
            }
            
            for(i=0;i<(int)(2+20*random()/RAND_MAX);i++){
                a=(int)(1+18*random()/RAND_MAX);
                b=(int)(1+18*random()/RAND_MAX);
                map[a][b]=2;
            }
            for(i=0;i<(int)(4+20*random()/RAND_MAX);i++){
                a=(int)(1+18*random()/RAND_MAX);
                b=(int)(1+18*random()/RAND_MAX);
                if(map[a][b]==2||(a==1&&b==1)||(a==18&&b==18)){
                    i-=1;continue;
                }
                map[a][b]=3;
            }
            for(i=0;i<(int)(3+20*random()/RAND_MAX);i++){
                a=(int)(1+18*random()/RAND_MAX);
                b=(int)(1+18*random()/RAND_MAX);
                if(map[a][b]==2||map[a][b]==3||(a==1&&b==1)||(a==18&&b==18)){
                    i-=1;continue;
                }
                map[a][b]=1;
            }
            for(i=0;i<(int)(3+20*random()/RAND_MAX);i++){
                a=(int)(1+18*random()/RAND_MAX);
                b=(int)(1+18*random()/RAND_MAX);
                if(map[a][b]==2||map[a][b]==3||(a==1&&b==1)||(a==18&&b==18)){
                    i-=1;continue;
                }
                map[a][b]=4;
           }
            for(i=0;i<enemy;i++){
                a=(int)(32+32*16*random()/RAND_MAX);
                b=(int)(32+32*16*random()/RAND_MAX);
                if(map[a/32][b/32]==2||map[a/32][b/32]==3||(a/32==1&&b/32==1)||(a/32==18&&b/32==18)){
                    i-=1;continue;
                }
                enemies[i].posx=a;
                enemies[i].posy=b;
                enemies[i].firstposx=a;
                enemies[i].firstposy=b;
                enemies[i].inform=0;
               if(i==enemy-1){
                    enemies[i].inform=1;
                }
                if(i==enemy-3){
                    enemies[i].inform=3;
                }
                if(i==enemy-2){
                    enemies[i].inform=2;
                }
            }}
        //    printf("%d\n",enemy);
            for(i=0;i<100;i++){
                for(j=0;j<100;j++){
                    previous[i][j]=map[i][j];
                    //printf("%d %d\n",previous[i][j],map[i][j]);
                }
            }
            fclose(fp);
          sprintf(zanki,"=%d",reborn);
        }
        
        count=1;
        for(i=0;i<100;i++){
            if(i==0){
                x=prev;
            }
            else{
                x+=32;
            }
            for(j=0;j<20;j++){
                if(j==0){
                    y=0;
                }
                if(map[i][j]==2&&trush[i][j]==50){
                    map[i][j]=0;
                    printf("宝箱が消滅してしまった！\n");
                }
                if(map[i][j]==2&&trush[i][j]!=50&&trush[i][j]!=0){
                    trush[i][j]++;
                }
                if(map[i][j]==2&& (i==playe[0]/32&&j==playe[1]/32)&&trush[i][j]==0){
                    trush[i][j]=1;
                }
                switch (map[i][j]) {
                    case 1:
                        PutSprite(img[2], x, y, &info[2]);
                        y+=32;
                        continue;
                    case 2:
                        PutSprite(img[3], x, y, &info[3]);
                        //      printf("%d\n",trush[i][j]);
                        y+=32;
                        continue;
                    case 3:
                        PutSprite(img[4], x, y, &info[4]);
                        y+=32;
                        continue;
                    case 4:
                        PutSprite(img[14], x, y, &info[14]);
                        y+=32;
                        continue;
                    case 9:
                        PutSprite(img[5], x, y, &info[5]);
                        y+=32;
                        continue;
                    default:
                        PutSprite(img[1], x, y, &info[1]);
                        y+=32;
                        continue;
                }
            }
        }
        // printf("%d\n",score);
       if(prev%32==0&&prev!=0){
            prev=0;
            for(i=0;i<100;i++){
                for(j=0;j<100;j++){
                map[i][j]=map[i+1][j];
                }
            }
        }
       if(run==1){
            for(i=0;i<enemy;i++){
                enemies[i].posx-=8;
            }
        }
        run=0;
        sprintf(scores,"SCORE:%4d",score);
        glRasterPos2i(32*11,25);
        for(i=0;i<strlen(scores);i++){
            glColor3ub(255,0,0);
            
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,scores[i]);
        }
        if (flying==1&&timer%2==0&&jumpng==1){
            playe[1]-=jumping;
            jumping--;
            
        }
       // printf("%d\n",jumping);
        if(jumping<0&&flying==1&&map[playe[0]/32][playe[1]/32+1]==1&&prev%32==0){
            flying=0;jumpng=0;
            fall=0;falling=0;
            jumping=16;//printf("a");
        }
        else if(jumping<0&&flying==1&&(map[playe[0]/32][playe[1]/32+1]==1||map[playe[0]/32+1][playe[1]/32+1]==1)&&prev%32!=0){
           flying=0;jumpng=0;
            fall=0;falling=0;
            jumping=16;//printf("c");
        }
        
        if(flying==0&&map[playe[0]/32][playe[1]/32+1]!=1&&prev%32==0&&timer%2==0){
       //     printf("%d %d\n",fall,playe[1]);
            falling=1;
            fall++;
            playe[1]+=fall;
         //  printf("%d %d\n",fall,playe[1]);
        }else if(flying==0&&map[playe[0]/32][playe[1]/32+1]!=1&&map[playe[0]/32+1][playe[1]/32+1]!=1&&prev%32!=0&&timer%2==0){
            falling=1;
            fall++;
            playe[1]+=fall;
        }
        if(flying==1&&map[playe[0]/32][playe[1]/32]==1&&prev%32==0){
            flying=0;
            falling=0;//printf("q");
            jumping=16;
        }
        else if(flying==1&&(map[playe[0]/32][playe[1]/32]==1||map[playe[0]/32+1][playe[1]/32]==1)&&prev%32!=0){
            flying=0;
            falling=0;//printf("z");
            jumping=16;
        }
        //printf("%d\n",falling);
        if(falling==0&&flying==0&&(map[playe[0]/32][playe[1]/32+1]==1||map[playe[0]/32+1][playe[1]/32+1]==1)){
            jumpng=0;
            playe[1]/=32;
            
            playe[1]*=32;
            
        }
        falling=0;
        for(i=0;i<20;i++){
            for(j=0;j<20;j++){
                if(map[i][j]==3){//printf("%d %d\n",playe[0]-i*32,playe[1]-j*32);
                    /*if(flying==1&&abs(playe[0]-i*32)<40&&abs(playe[1]-j*32)<40){
                        now=3;
                    }*/
                    if(abs(playe[0]-i*32)<32&&abs(playe[1]-j*32)<32&&reborn==0){
                        now=3;
                        
                    }
                    if(abs(playe[0]-i*32)<32&&abs(playe[1]-j*32)<32&&reborn!=0){
                        now=4;//printf("d\n");
                        
                    }
                }
            }
        }
        for(i=0;i<enemy;i++){
            if(enemies[i].dead!=0){
                continue;
            }
            if(abs(playe[0]-enemies[i].posx)<32&&(playe[1]-enemies[i].posy)>-32&&(playe[1]-enemies[i].posy)<0){
                flying=1;
                fall=0;
                jumping=16;
                enemies[i].dead=1;
                score+=1000;
                //printf("alpha\n");
            }
            if(enemies[i].dead!=0){
                continue;
            }
            if(enemies[i].inform==0){
                PutSprite(img[10], enemies[i].posx, enemies[i].posy, &info[10]);
            }
            if(enemies[i].inform==1){
            PutSprite(img[10], enemies[i].posx, enemies[i].posy, &info[10]);
            }
            if(enemies[i].inform==2){
                PutSprite(img[11], enemies[i].posx, enemies[i].posy, &info[11]);
            }
            if(enemies[i].inform==3){
                PutSprite(img[12], enemies[i].posx, enemies[i].posy, &info[12]);
            }
            
            if(abs(playe[0]-enemies[i].posx)<32&&abs(playe[1]-enemies[i].posy)<32&&reborn==0){
             
                now=3;
                
            }
            if(abs(playe[0]-enemies[i].posx)<32&&abs(playe[1]-enemies[i].posy)<32&&reborn!=0){
               
                now=4;//printf("c %d %d %d %d\n",i,enemies[i].posx,enemies[i].posy,enemies[i].inform);
                
            }
        }
        if(bullet==1){
            if(bulletpos[0]>32*19){
                bullet=0;
            }
         //   printf("%d,%d\n",arms,bullet);
            if(map[bulletpos[0]/32+1][bulletpos[1]/32]==1){
                bullet=0; }
            bulletpos[0]+=16;
           PutSprite(img[13], bulletpos[0], bulletpos[1], &info[13]);
        
        for(i=0;i<enemy;i++){
            if(enemies[i].dead==1){
                continue;
            }
            if(abs(bulletpos[0]-enemies[i].posx)<32&&abs(bulletpos[1]-enemies[i].posy)<32){
                enemies[i].wound++;
                bullet=0;
                score+=1000;
            }
            if(enemies[i].wound==5){
                enemies[i].dead=1;
            }
        }
        }
        if(score%30000==0&&score!=0&&strain==0){
            reborn++;strain=1;
        }
        if(score%30000!=0){
            strain=0;
        }
      // printf("%d %d %d\n",enemies[enemy-3].posx,enemies[enemy-3].posy,enemies[i].inform);
    
        for(i=0;i<enemy;i++){
            if(enemies[i].dead!=0){
                continue;
            }
            if(enemies[i].posy>32*21){
                enemies[i].dead=1;
            }
            if(enemies[i].dead!=0){
                continue;
            }
            if(enemies[i].inform==2&&abs(playe[0]-enemies[i].posx)<32*2){
                enemies[i].posy+=16;
                if(map[enemies[i].posx/32][enemies[i].posy/32]!=0&&enemies[i].posx-1%32==0){
                    map[enemies[i].posx/32][enemies[i].posy/32]=0;
                }
                if(map[enemies[i].posx/32+1][enemies[i].posy/32]!=0&&enemies[i].posx-1%32!=0){
                    map[enemies[i].posx/32+1][enemies[i].posy/32]=0;
                }
               
            }
            if(enemies[i].inform==3&&abs(playe[0]-enemies[i].posx)>32*5&&(playe[0]-enemies[i].posx)<32*7){
                enemies[i].posx=playe[0]+32*2;
            }
            if(enemies[i].inform==2){
                continue;
            }
            if(enemies[i].fly!=1&&playe[1]<=enemies[i].posy&&abs(playe[0]-enemies[i].posx)<32*3&&enemies[i].inform==1){
                enemies[i].fly=1;enemies[i].jumpin=16;
            }
            if (enemies[i].fly==1&&timer%2==0){
                enemies[i].posy-=enemies[i].jumpin;
                enemies[i].jumpin--;
                
            }
            // printf("%d\n",enemies[i].jumpin);
            if(enemies[i].jumpin<0&&enemies[i].fly==1&&map[enemies[i].posx/32][enemies[i].posy/32+1]==1&&prev%32==0){
                enemies[i].fly=0;
                enemies[i].jumpin=16;//printf("a");
            }
            else if(enemies[i].jumpin<0&&enemies[i].fly==1&&(map[enemies[i].posx/32][enemies[i].posy/32+1]==1||map[enemies[i].posx/32+1][enemies[i].posy/32+1]==1)&&prev%32!=0){
                enemies[i].fly=0;
                enemies[i].jumpin=16;//printf("c");
            }
            if(enemies[i].fly==1&&map[enemies[i].posx/32][enemies[i].posy/32-1]==1&&prev%32==0){
                enemies[i].fly=0;
                enemies[i].jumpin=16;
            }
            else if(enemies[i].fly==1&&(map[enemies[i].posx/32][enemies[i].posy/32-1]==1||map[enemies[i].posx/32+1][enemies[i].posy/32-1]==1)&&prev%32!=0){
                enemies[i].fly=0;
                enemies[i].jumpin=16;
            }
            if(enemies[i].fly!=1&&map[enemies[i].posx/32][enemies[i].posy/32+1]!=1&&enemies[i].posx%32==0){
                
                enemies[i].posy+=4;
            }
            else if(enemies[i].fly!=1&&map[enemies[i].posx/32][enemies[i].posy/32+1]!=1&&map[enemies[i].posx/32+1][enemies[i].posy/32+1]!=1&&enemies[i].posx%32!=0){
              
                enemies[i].posy+=4;
            }
            if(enemies[i].fly!=1&&map[enemies[i].posx/32][enemies[i].posy/32+1]==1&&map[enemies[i].posx/32+1][enemies[i].posy/32+1]==1){
                enemies[i].posy/=32;
                enemies[i].posy*=32;
            }

        }
     //   printf("b %d %d\n",enemies[i].jumpin,map[enemies[i].posx/32+1][enemies[i].posy/32+1]);
        if(playe[1]>32*19&&reborn==0){
            now=3;
        }
        if(playe[1]>32*19&&reborn!=0){
            now=4;//printf("b\n");
        }

        PutSprite(img[5], playe[0], playe[1], &info[5]);
        if(map[playe[0]/32][playe[1]/32]==9){
            now=2;
        }
        if(arms==1){
            PutSprite(img[16], 32*9, 0, &info[16]);
        }
        if(arms==2){
            PutSprite(img[14], 32*9, 0, &info[14]);
        }
        timer++;
        if(timer==70){
            timer=0;
            nowt--;
            for(i=0;i<enemy;i++){
                if(enemies[i].posx<0){
                    continue;
                }
                if(map[enemies[i].posx/32-1][enemies[i].posy/32]!=1&&map[enemies[i].posx/32-1][enemies[i].posy/32]!=3&&enemies[i].posx<32*20){
                    enemies[i].posx-=8;//continue;
                }
                
                
            }
            
        }
        PutSprite(img[5], 32*7, 0, &info[5]);
        glRasterPos2i(32*8,25);
        for(i=0;i<strlen(zanki);i++){
            glColor3ub(255,0,0);
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,zanki[i]);
        }
        sprintf(timess,"TIME:%1d",nowt);
        glRasterPos2i(32*16,25);
        for(i=0;i<strlen(timess);i++){
            glColor3ub(255,0,0);
            
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,timess[i]);
        }
        if(nowt==0&&reborn==0){
            now=3;
        }
        if(nowt==0&&reborn!=0){
            now=4;
          //  printf("a\n");
        }
    }
    
    glFlush();
}
void PutSprite(int num, int x, int y, pngInfo *info){
    
    int w, h;
    
    
    w=info->Width;
    h=info->Height;
    
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, num);
    glColor4ub(255, 255, 255, 255);
    
    glBegin(GL_QUADS);
    
    glTexCoord2i(0, 0);
    glVertex2i(x,y);
    
    glTexCoord2i(0,1);
    glVertex2i(x, y+h);
    
    glTexCoord2i(1, 1);
    glVertex2i(x+w, y+h);
    
    glTexCoord2i(1, 0);
    glVertex2i(x+w, y);
    
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
}
void KeyBoard(unsigned char key,int x,int y){
    a=glutGetModifiers();
    if(key==32){
        if(map[playe[0]/32][playe[1]/32-1]==1&&prev%32==0){
            //    printf("通れません\n");
            
        }
        else if((map[playe[0]/32][playe[1]/32-1]==1||map[playe[0]/32+1][playe[1]/32-1]==1)&&prev%32!=0)
            if(map[playe[0]/32][playe[1]/32-1]==3&&reborn==0){
                //  printf("爆発四散　GAMEOVER\n");
                now=3;
                
            }
        if(map[playe[0]/32][playe[1]/32-1]==3&&reborn!=0){
            //  printf("爆発四散　GAMEOVER\n");
            now=4;
            
        }
        if(flying==0&&jumpng==0){
            flying=1;jumping=16;fall=0;falling=0,jumpng=1;}
        
    }
    if(map[playe[0]/32][playe[1]/32]==2){
        if(key=='t'){
            printf("宝箱を取得した!\n");
            map[playe[0]/32][playe[1]/32]=0;
            score+=1000;arms=1;
        }
    }
    if(map[playe[0]/32-1][playe[1]/32]==2){
        if(key=='t'){
            printf("宝箱を取得した!\n");
            map[playe[0]/32][playe[1]/32]=0;
            score+=1000;arms=1;
        }
    }
    if(map[playe[0]/32+1][playe[1]/32]==2){
        if(key=='t'){
            printf("宝箱を取得した!\n");
            map[playe[0]/32+1][playe[1]/32]=0;
            score+=1000;arms=1;
        }
    }
    if(map[playe[0]/32][playe[1]/32]==4){
        if(key=='t'){
            printf("宝箱を取得した!\n");
            map[playe[0]/32][playe[1]/32]=0;
            score+=1000;arms=2;burst=20;
        }
    }
    if(map[playe[0]/32-1][playe[1]/32]==4){
        if(key=='t'){
            printf("宝箱を取得した!\n");
            map[playe[0]/32][playe[1]/32]=0;
            score+=1000;arms=2;burst=20;
        }
    }
    if(map[playe[0]/32+1][playe[1]/32]==4){
        if(key=='t'){
            printf("宝箱を取得した!\n");
            map[playe[0]/32+1][playe[1]/32]=0;
            score+=1000;arms=2;burst=20;
        }
    }
    if((key=='r'||key=='R')&&now==4){
        now=1;playe[0]=33;playe[1]=32*18;nowt=100;prev=0;flying=0;
        jumping=16;arms=0;bullet=0;burst=0;reborn--;sprintf(zanki,"=%d",reborn);
        fall=0;
        for(i=0;i<100;i++){
            for(j=0;j<100;j++){
                map[i][j]=previous[i][j];
            }
        }
        for(i=0;i<enemy;i++){
            enemies[i].posy=enemies[i].firstposy;
            enemies[i].posx=enemies[i].firstposx;
            enemies[i].fall=0;
            enemies[i].fly=0;
            enemies[i].jumpin=0;
            enemies[i].dead=0;
            enemies[i].damage=0;
             enemies[i].wound=0;
        }
    }
    if((key==18)&&((a&GLUT_ACTIVE_CTRL)!=0)&&(now==2)){
        count=0;now=1;playe[0]=33;playe[1]=32*18;nowt=100;prev=0;flying=0;
        jumping=16;arms=0;bullet=0;burst=0;reborn=3;
        fall=0;stage++;
        if(stage==5){
            now=7;
        }
        reborn=3;
        for(i=0;i<enemy;i++){
            enemies[i].fall=0;
            enemies[i].fly=0;
            enemies[i].jumpin=0;
            enemies[i].damage=0;
            enemies[i].wound=0;
            enemies[i].dead=0;
        }
    }

    if((key==18)&&((a&GLUT_ACTIVE_CTRL)!=0)&&(now==3)&&reborn==0){
        count=0;now=1;playe[0]=33;playe[1]=32*18;nowt=100;prev=0;flying=0;
        jumping=16;arms=0;bullet=0;burst=0;reborn=3;score=0;
        fall=0;
        reborn=3;
        for(i=0;i<enemy;i++){
            enemies[i].fall=0;
            enemies[i].fly=0;
            enemies[i].jumpin=0;
            enemies[i].dead=0;
            enemies[i].damage=0;
            enemies[i].wound=0;
        }
    }

    if((key==19)&&((a&GLUT_ACTIVE_CTRL)!=0)){
        now=1;
    }
    if((key==5)&&((a&GLUT_ACTIVE_CTRL)!=0)&&(now==2||now==3)){
        exit(-1);
    }
    if((key=='e'||key=='E')&&(now==4)){
        exit(-1);
    }
    
    if(key=='f'&&arms==1){
        for(i=0;i<enemy;i++){
            if(abs(playe[0]-enemies[i].posx)<48&&abs(playe[1]-enemies[i].posy)<32){
                enemies[i].posx+=64;
                enemies[i].posy-=32;
                enemies[i].damage++;
                if(enemies[i].damage==3){
                    enemies[i].dead=1;score+=1000;
                }
            }
        }
    }
    if(key=='f'&&arms==2&&bullet==0&&burst!=0){
        bullet=1;burst--;
        bulletpos[0]=playe[0];
        bulletpos[1]=playe[1];
    }
}
void SpecialKey(int key,int x,int y){
    switch(key){
    /*    case GLUT_KEY_UP:
            if(map[playe[0]/32][playe[1]/32-1]==1&&prev%32==0){
            //    printf("通れません\n");
                break;
            }
            else if((map[playe[0]/32][playe[1]/32-1]==1||map[playe[0]/32+1][playe[1]/32-1]==1)&&prev%32!=0)
            if(map[playe[0]/32][playe[1]/32-1]==3&&reborn==0){
              //  printf("爆発四散　GAMEOVER\n");
                now=3;
                break;
            }
            if(map[playe[0]/32][playe[1]/32-1]==3&&reborn!=0){
                //  printf("爆発四散　GAMEOVER\n");
                now=4;
                 break;
            }
            if(flying==0){
                flying=1;jumping=16;fall=0;falling=0;}
        
       case GLUT_KEY_DOWN:
            if(map[playe[0]/32][playe[1]/32+1]==1){
                printf("通れません\n");
                break;
            }
            if(map[playe[0]/32][playe[1]/32+1]==3){
                printf("爆発四散　GAMEOVER\n");
                now=3;
                break;
            }
            playe[1]+=32;
            break;*/
        case GLUT_KEY_RIGHT:
            if(map[playe[0]/32+1][playe[1]/32]==1){
             //   print("通れません\n");
             break;
            }
            if(map[playe[0]/32+1][playe[1]/32]==3&&reborn==0){
                //printf("爆発四散　GAMEOVER\n");
                now=3;
                 break;
            }
            if(map[playe[0]/32+1][playe[1]/32]==3&&reborn!=0){
                //printf("爆発四散　GAMEOVER\n");
                now=4;
                 break;
            }
            prev-=8;run=1;
             break;
        case GLUT_KEY_LEFT:
            if(map[playe[0]/32-1][playe[1]/32]==1){
           //     printf("通れません\n");
                 break;
            }
            if(map[playe[0]/32-1][playe[1]/32]==3&&reborn==0){
            //    printf("爆発四散　GAMEOVER\n");
                now=3;
                 break;
            }
            if(map[playe[0]/32-1][playe[1]/32]==3&&reborn!=0){
                //    printf("爆発四散　GAMEOVER\n");
                now=4;
                 break;
            }
          prev+=8;
         break;
    }
}
void Timer(int t){
    
    glutPostRedisplay();
    glutTimerFunc(1, Timer, 0);
    
}
/*void Motion(int x,int y){
    printf("Motion :(x,y)=(%d,%d)\n",x,y);
}*/

void mouse(int b,int s,int x,int y){
    if(b==GLUT_LEFT_BUTTON){
       
        if(s==GLUT_DOWN&&now==0&&y>270&&y<350){
            now=1;
          //  printf("左ボタンダウン\n");
        }
        if(s==GLUT_DOWN&&now==0&&y>400&&y<500){
            now=9;
            //  printf("左ボタンダウン\n");
        }
        
        if(s==GLUT_DOWN&&now==0&&y>500&&y<600){
            now=5;//printf("%d\n",now);
        }
        if(s==GLUT_DOWN&&now==5&&y>550&&y<800){
            now=0;//printf("%d\n",now);
        }
    }
   
}

