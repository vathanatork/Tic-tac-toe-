#include<unistd.h>
#include<string.h>
#include<gtk/gtk.h>
#include<gtk/gtkx.h>
#include<math.h>
#include<ctype.h>
#include<time.h>

//make them global

GtkWidget     *window;
GtkWidget	  *fixed;
GtkWidget     *button1;
GtkWidget     *button2;
GtkWidget     *button3;
GtkWidget     *button4;
GtkWidget     *button5;
GtkWidget     *button6;
GtkWidget     *button7;
GtkWidget     *button8;
GtkWidget     *button9;

GtkWidget     *label1;
GtkWidget     *label2;
GtkWidget     *label3;
GtkWidget     *label4;
GtkWidget     *label5;
GtkWidget     *label6;
GtkWidget     *label7;
GtkWidget     *label8;
GtkWidget     *label9;
GtkWidget     *boxbackframe;
GtkBuilder    *builder;
GtkWidget     *playtime;
GtkWidget     *winner;
GtkWidget     *refreshbutton;

int index_click=0;
//number of click if index_click%2==0 "O player1" index_click%2==1 "x player2"
int click[3][3]={{0,0,0},
                 {0,0,0},
                 {0,0,0}};
//if click value 0 so the button have been click it will give label value
// when button have been click (click will change to 1 if(player1) or 2 if(player2)
int stop_play=4;
// when check_win()=win ,click = stop_play.So all button will not give value to label when its is click;
int play=0;

static void on_button1(GtkWidget *button1,GtkWidget *label1);
static void on_button2(GtkWidget *button2,GtkWidget *label2);
static void on_button3(GtkWidget *button3,GtkWidget *label3);
static void on_button4(GtkWidget *button4,GtkWidget *label4);
static void on_button5(GtkWidget *button5,GtkWidget *label5);
static void on_button6(GtkWidget *button6,GtkWidget *label6);
static void on_button7(GtkWidget *button7,GtkWidget *label7);
static void on_button8(GtkWidget *button8,GtkWidget *label8);
static void on_button9(GtkWidget *button9,GtkWidget *label9);
//static gboolean time_play(GtkWidget *playtime);
static void refresh(GtkWidget *refreshbutton);
void check_win(void);
void stop(void);


int main(int argc, char* argv[]){

	gtk_init(&argc,&argv);//init Gtk
//................................................................
// establish contact with xml code used to adjust widget settings
//................................................................

	builder = gtk_builder_new_from_file ("tictactoe.glade");
	window = GTK_WIDGET(gtk_builder_get_object(builder,"window"));
	g_signal_connect(window,"destroy", G_CALLBACK(gtk_main_quit),NULL);
	gtk_builder_connect_signals(builder,NULL);
    //referent button
	fixed= GTK_WIDGET(gtk_builder_get_object(builder,"fixed"));
	button1=GTK_WIDGET(gtk_builder_get_object(builder,"button1"));
	button2=GTK_WIDGET(gtk_builder_get_object(builder,"button2"));
    button3=GTK_WIDGET(gtk_builder_get_object(builder,"button3"));
    button4=GTK_WIDGET(gtk_builder_get_object(builder,"button4"));
    button5=GTK_WIDGET(gtk_builder_get_object(builder,"button5"));
    button6=GTK_WIDGET(gtk_builder_get_object(builder,"button6"));
    button7=GTK_WIDGET(gtk_builder_get_object(builder,"button7"));
    button8=GTK_WIDGET(gtk_builder_get_object(builder,"button8"));
    button9=GTK_WIDGET(gtk_builder_get_object(builder,"button9"));
    refreshbutton=GTK_WIDGET(gtk_builder_get_object(builder,"refreshbutton"));
    boxbackframe=GTK_WIDGET(gtk_builder_get_object(builder,"boxbackframe"));


    //referent label
	label1= GTK_WIDGET(gtk_builder_get_object(builder,"label1"));
	label2= GTK_WIDGET(gtk_builder_get_object(builder,"label2"));
    label3= GTK_WIDGET(gtk_builder_get_object(builder,"label3"));
    label4= GTK_WIDGET(gtk_builder_get_object(builder,"label4"));
    label5= GTK_WIDGET(gtk_builder_get_object(builder,"label5"));
    label6= GTK_WIDGET(gtk_builder_get_object(builder,"label6"));
    label7= GTK_WIDGET(gtk_builder_get_object(builder,"label7"));
    label8= GTK_WIDGET(gtk_builder_get_object(builder,"label8"));
    label9= GTK_WIDGET(gtk_builder_get_object(builder,"label9"));
    playtime= GTK_WIDGET(gtk_builder_get_object(builder,"playtime"));
    winner= GTK_WIDGET(gtk_builder_get_object(builder,"winner"));


    //callback funtion
    //guint ID = g_timeout_add_seconds(1, (GSourceFunc) time_play,playtime);

    g_signal_connect(button1,"pressed",G_CALLBACK(on_button1),label1);
    g_signal_connect(button2,"pressed",G_CALLBACK(on_button2),label2);
    g_signal_connect(button3,"pressed",G_CALLBACK(on_button3),label3);
    g_signal_connect(button4,"pressed",G_CALLBACK(on_button4),label4);
    g_signal_connect(button5,"pressed",G_CALLBACK(on_button5),label5);
    g_signal_connect(button6,"pressed",G_CALLBACK(on_button6),label6);
    g_signal_connect(button7,"pressed",G_CALLBACK(on_button7),label7);
    g_signal_connect(button8,"pressed",G_CALLBACK(on_button8),label8);
    g_signal_connect(button9,"pressed",G_CALLBACK(on_button9),label9);
    g_signal_connect(refreshbutton,"pressed",G_CALLBACK(refresh),NULL);

    gtk_label_set_text(GTK_LABEL(winner),"Player1 Walk!");

    //color window
    GdkColor color;//default background color
    color.red=0xd1ccc;
    color.green=0xd7ccc;
    color.blue = 0xd9ccc;
    gtk_widget_modify_bg(GTK_WIDGET(window), GTK_STATE_NORMAL, &color);


    color.red=0xd94ccc;
    color.green=0xd9ccc;
    color.blue = 0xccc;
    gtk_widget_modify_bg(GTK_WIDGET(boxbackframe), GTK_STATE_NORMAL, &color);


    //show window
	gtk_widget_show(window);
	gtk_main();
	return EXIT_SUCCESS;

}

//funtion
static void on_button1(GtkWidget *button1,GtkWidget *label1){

    if(click[0][0]==0)
    {
        if((index_click%2)==0)
        {
            gtk_label_set_text(GTK_LABEL(label1),"O");
            click[0][0]+=1;
            gtk_label_set_text(GTK_LABEL(winner),"Player2 Walk!");
        }
        if((index_click%2)==1)
        {
            gtk_label_set_text(GTK_LABEL(label1),"X");
            click[0][0]+=2;
            gtk_label_set_text(GTK_LABEL(winner),"Player1 Walk!");
        }
        index_click+=1;
        g_printf("index_click %d",index_click);
        g_printf("\tplayer %d\n",click[0][0]);
        check_win();
    }
}

static void on_button2(GtkWidget *button2,GtkWidget *label2){

    if(click[0][1]==0)
    {
        if((index_click%2)==0)
        {
            gtk_label_set_text(GTK_LABEL(label2),"O");
            click[0][1]+=1;
            gtk_label_set_text(GTK_LABEL(winner),"Player2 Walk!");
        }
        if((index_click%2)==1)
        {
            gtk_label_set_text(GTK_LABEL(label2),"X");
            click[0][1]+=2;
            gtk_label_set_text(GTK_LABEL(winner),"Player1 Walk!");
        }
        index_click+=1;
        g_printf("index_click %d",index_click);
        g_printf("\tplayer %d\n",click[0][1]);
        check_win();
    }
}

static void on_button3(GtkWidget *button3,GtkWidget *label3){

    if(click[0][2]==0)
    {
        if((index_click%2)==0)
        {
            gtk_label_set_text(GTK_LABEL(label3),"O");
             click[0][2]+=1;
             gtk_label_set_text(GTK_LABEL(winner),"Player2 Walk!");
        }
        if((index_click%2)==1)
        {
            gtk_label_set_text(GTK_LABEL(label3),"X");
             click[0][2]+=2;
             gtk_label_set_text(GTK_LABEL(winner),"Player1 Walk!");
        }
        index_click+=1;
        g_printf("index_click %d",index_click);
        g_printf("\tplayer %d\n",click[0][2]);
        check_win();
    }
}

static void on_button4(GtkWidget *button4,GtkWidget *label4){

    if(click[1][0]==0)
    {
        if((index_click%2)==0)
        {
            gtk_label_set_text(GTK_LABEL(label4),"O");
            click[1][0]+=1;
            gtk_label_set_text(GTK_LABEL(winner),"Player2 Walk!");
        }
        if((index_click%2)==1)
        {
            gtk_label_set_text(GTK_LABEL(label4),"X");
            click[1][0]+=2;
            gtk_label_set_text(GTK_LABEL(winner),"Player1 Walk!");
        }
        index_click+=1;
        g_printf("index_click %d",index_click);
        g_printf("\tplayer %d\n",click[1][0]);
        check_win();
    }
}

static void on_button5(GtkWidget *button5,GtkWidget *label5){

    if(click[1][1]==0)
    {
        if((index_click%2)==0)
        {
            gtk_label_set_text(GTK_LABEL(label5),"O");
            click[1][1]+=1;
            gtk_label_set_text(GTK_LABEL(winner),"Player2 Walk!");
        }
        if((index_click%2)==1)
        {
            gtk_label_set_text(GTK_LABEL(label5),"X");
            click[1][1]+=2;
            gtk_label_set_text(GTK_LABEL(winner),"Player1 Walk!");
        }
        index_click+=1;
        g_printf("index_click %d",index_click);
        g_printf("\tplayer %d\n",click[1][1]);
        check_win();
    }
}

static void on_button6(GtkWidget *button6,GtkWidget *label6){

    if(click[1][2]==0)
    {
        if((index_click%2)==0)
        {
            gtk_label_set_text(GTK_LABEL(label6),"O");
            click[1][2]+=1;
            gtk_label_set_text(GTK_LABEL(winner),"Player2 Walk!");
        }
        if((index_click%2)==1)
        {
            gtk_label_set_text(GTK_LABEL(label6),"X");
            click[1][2]+=2;
            gtk_label_set_text(GTK_LABEL(winner),"Player1 Walk!");
        }
        index_click+=1;
        g_printf("index_click %d",index_click);
        g_printf("\tplayer %d\n",click[1][2]);
        check_win();
    }
}

static void on_button7(GtkWidget *button7,GtkWidget *label7){

    if(click[2][0]==0)
    {
        if((index_click%2)==0)
        {
            gtk_label_set_text(GTK_LABEL(label7),"O");
            click[2][0]+=1;
            gtk_label_set_text(GTK_LABEL(winner),"Player2 Walk!");
        }
        if((index_click%2)==1)
        {
            gtk_label_set_text(GTK_LABEL(label7),"X");
            click[2][0]+=2;
            gtk_label_set_text(GTK_LABEL(winner),"Player1 Walk!");
        }
        index_click+=1;
        g_printf("index_click %d",index_click);
        g_printf("\tplayer %d\n",click[2][0]);
        check_win();
    }
}

static void on_button8(GtkWidget *button8,GtkWidget *label8){

    if(click[2][1]==0)
    {
        if((index_click%2)==0)
        {
            gtk_label_set_text(GTK_LABEL(label8),"O");
            click[2][1]+=1;
            gtk_label_set_text(GTK_LABEL(winner),"Player2 Walk!");
        }
        if((index_click%2)==1)
        {
            gtk_label_set_text(GTK_LABEL(label8),"X");
            click[2][1]+=2;
            gtk_label_set_text(GTK_LABEL(winner),"Player1 Walk!");
        }
        index_click+=1;
        g_printf("index_click %d",index_click);
        g_printf("\tplayer %d\n",click[2][1]);
        check_win();
    }
}

static void on_button9(GtkWidget *button9,GtkWidget *label9){

    if(click[2][2]==0)
    {
        if((index_click%2)==0)
        {
            gtk_label_set_text(GTK_LABEL(label9),"O");
            click[2][2]+=1;
            gtk_label_set_text(GTK_LABEL(winner),"Player2 Walk!");
        }
        if((index_click%2)==1)
        {
            gtk_label_set_text(GTK_LABEL(label9),"X");
            click[2][2]+=2;
            gtk_label_set_text(GTK_LABEL(winner),"Player1 Walk!");
        }
        index_click+=1;
        g_printf("index_click %d",index_click);
        g_printf("\tplayer %d\n",click[2][2]);
        check_win();
    }
}

/*static gboolean time_play(GtkWidget *playtime){
    time_t t = time(0);
    gtk_label_set_text(GTK_LABEL(playtime), ctime(&t));
    return TRUE;
}*/

 void check_win(){
    for(int i=0;i<3;i++)
    {   //row win
       if(click[i][0]==click[i][1]&&click[i][1]==click[i][2])
        {
            if(click[i][0]==1)
            {
                gtk_label_set_text(GTK_LABEL(winner),"Player1 win");
                printf("\nplayer1 win\n");
                stop();
                break;
            }
            else if(click[i][0]==2)
            {
                gtk_label_set_text(GTK_LABEL(winner),"Player2 win");
                printf("\nPlayer2 win\n");
                stop();
                break;
            }
        }
        //column
        else if(click[0][i]==click[1][i]&&click[1][i]==click[2][i])
        {
            if(click[0][i]==1)
            {
                gtk_label_set_text(GTK_LABEL(winner),"Player1 win");
                printf("\nplayer1 win\n");
                stop();
                break;
            }
            else if(click[0][i]==2)
            {
                gtk_label_set_text(GTK_LABEL(winner),"Player2 win");
                printf("\nPlayer2 win\n");
                stop();
                break;
            }
        }
    }
    //dialog
    if(click[0][0]==click[1][1]&&click[1][1]==click[2][2])
    {
        if(click[0][0]==1)
        {
            gtk_label_set_text(GTK_LABEL(winner),"Player1 win");
            printf("\nplayer1 win\n");
            stop();
        }
        else if(click[0][0]==2)
        {
            gtk_label_set_text(GTK_LABEL(winner),"Player2 win");
            printf("\nPlayer2 win\n");
            stop();
        }
    }
    else if(click[2][0]==click[1][1]&&click[1][1]==click[0][2])
    {
       if(click[2][0]==1)
        {
            gtk_label_set_text(GTK_LABEL(winner),"Player1 win");
            printf("\nplayer1 win\n");
            stop();
        }
        else if(click[2][0]==2)
        {
            gtk_label_set_text(GTK_LABEL(winner),"Player2 win");
            printf("\nPlayer2 win\n");
            stop();
        }
    }
    //draw
    else if((click[0][0]&&click[0][1]&&click[0][2])!=0)
    {
        if((click[1][0]&&click[1][1]&&click[1][2])!=0)
        {
            if((click[2][0]&&click[2][1]&&click[2][2])!=0)
            {
                gtk_label_set_text(GTK_LABEL(winner),"Draw!");
                printf("Draw");
            }
        }
    }
}

//stop when someone win
void stop(void){

    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            click[i][j]=stop_play;
        }
    }printf("\nclick=%d\n",stop_play);
}

//refreshfuntion
static void refresh(GtkWidget *refreshbutton){

    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            click[i][j]=play;
            index_click=0;
        }
    }
    printf("\ncan play again click=%d\n",play);
    printf("\nindex_click=0\n");
    gtk_label_set_text(GTK_LABEL(label1),"");
    gtk_label_set_text(GTK_LABEL(label2),"");
    gtk_label_set_text(GTK_LABEL(label3),"");
    gtk_label_set_text(GTK_LABEL(label4),"");
    gtk_label_set_text(GTK_LABEL(label5),"");
    gtk_label_set_text(GTK_LABEL(label6),"");
    gtk_label_set_text(GTK_LABEL(label7),"");
    gtk_label_set_text(GTK_LABEL(label8),"");
    gtk_label_set_text(GTK_LABEL(label9),"");
    gtk_label_set_text(GTK_LABEL(winner),"Player1 WALK!");
}
