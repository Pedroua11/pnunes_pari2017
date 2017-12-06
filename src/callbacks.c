/**
 *       @file  callbacks.c
 *      @brief  Breve Descrição
 *
 * Descrição mais detalhada do ficheiro que até poderiam incluir links para imagens etc.
 *
 *     @author  Pedro Nunes, pnunes@ua.pt
 *
 *   @internal
 *     Created  29-Nov-2017
 *     Company  University of Aveiro
 *   Copyright  Copyright (c) 2017, Pedro Nunes
 *
 * =====================================================================================
 */
#include "myf.h"

/**
 * @brief  
 * @param  
 * @return 
 */
        //double xoffG = 100;
	//double yoffG = 120;
void p_RedrawText(cairo_t *cr)
{

  const char *font=" FreeSans";                //name of the font to use.
  char string[200];                       //aux string to put some text
  cairo_set_source_rgb(cr, 1, 0, 0);      //set color of the text (in RGB)

  //Below, a simple function to write text. If you need more sophisticated text rendering use pango instead.
  //cairo_select_font_face(cr, font, CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
  cairo_set_font_size(cr, fontSizeFactorG);          //adjust font size
cairo_set_font_size(cr, 20.0*fontSizeFactorG);

        time_t timep=time(NULL);
        struct tm *tm=localtime(&timep);
        cairo_select_font_face(cr, "Courier", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
if(tm->tm_sec%2)
        sprintf(string,"%02d:%02d:%02d", tm->tm_hour, tm->tm_min, tm->tm_sec);
else
	sprintf(string,"%02d %02d %02d", tm->tm_hour, tm->tm_min, tm->tm_sec);
  //sprintf(string,"My first cairo test");  //the actual string to render
  cairo_move_to(cr, xoffG, yoffG);        //place the text on the "surface"
  cairo_show_text(cr, string); 

}

void p_RedrawFreeForm(cairo_t * cr)
{
 	cairo_set_source_rgb(cr, 0, 1, 0);  //define a cor (rgb)
        cairo_set_line_width(cr, 1);        //impõe largura de linha

        int i;
        cairo_move_to(cr, ffG.x[0], ffG.y[0]);  //inicia o path
        for(i = 1; i < ffG.count; i++)          //percorre os pontos todos acumulados
        {
                cairo_line_to(cr, ffG.x[i], ffG.y[i]);  //atualiza o "path" segmento a segmento
        }
        cairo_stroke(cr);     //"imprime" o path na "surface" (neste caso será a drawing area)

}
void on_drawingarea1_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
        p_RedrawText(cr);
        p_RedrawFreeForm(cr);
}


void on_mouse_button_on(GtkWidget *widget, GdkEventButton *event, gpointer user_data)
{
	
	
        if( event->button == 2 )
        {
printf("pressed\n");
         ffG.count=0;
        }
               gtk_widget_queue_draw(widget);  //force redraw the widget


}




void on_drawingarea1_scroll_event(GtkWidget *widget,   GdkEventScroll *event, gpointer user_data)
        
       
{
  switch(event->direction)
        {
                case GDK_SCROLL_UP:
                        fontSizeFactorG+=0.1;  //increase factor
                        break;

                case GDK_SCROLL_DOWN:
                        fontSizeFactorG-=0.1;  //decrease factor
                        break;

                case GDK_SCROLL_LEFT:
                case GDK_SCROLL_RIGHT:
                case GDK_SCROLL_SMOOTH:
                        break;
        }
         gtk_widget_queue_draw(widget);  //force redraw the widget

}





void on_drawingarea1_motion_notify_event(GtkWidget *widget, GdkEventMotion *event, gpointer user_data)
{
 if( event->state & GDK_BUTTON3_MASK) //button 3 move text se carregar no botão 3
        {
                xoffG = event->x;  /*mouse coordinate x */ 
		//printf("x=%d\n",xoffG);
                yoffG = event->y;  /*mouse coordinate y */
		//printf("y=%d\n",yoffG);
        }
  if( event->state & GDK_BUTTON1_MASK)
  {
        if( ffG.x[ffG.count] != event->x && ffG.y[ffG.count] != event->y)
        {
                ffG.x[ffG.count]   = event->x;
                ffG.y[ffG.count++] = event->y;
                ffG.count %= MAXFFBUFFER; //se contador chegar ao limite, dá a volta
        }
  }

        gtk_widget_queue_draw(widget);  //force redraw the widget
	
}

gboolean p_ForceRefreshDA(gpointer user_data)
{
        GtkWidget *da;
        if( ! user_data)
           da = GTK_WIDGET(gtk_builder_get_object (builderG, "drawingarea1"));
        else
           da=GTK_WIDGET(user_data);

        //gdk_window_invalidate_rect (gtk_widget_get_window(da), NULL, FALSE); //would make draw parent window
        gtk_widget_queue_draw(da);  //make draw the widget

        return TRUE;  //continue running
}






void p_InitTimer()
{
  //Get widget ID for "drawingarea1"
  GtkWidget *da=GTK_WIDGET(gtk_builder_get_object (builderG, "drawingarea1"));
  //define timeout (timer): interval, callback to execute, and pass the window ID to refresh
  g_timeout_add (200, p_ForceRefreshDA, da); //em milissegundos
}


gboolean pari_UpdateImageAreas(gpointer data)
{
        //generate an expose event (draw event) on drawingarea1
        GtkWidget *da1 = GTK_WIDGET(gtk_builder_get_object(builderG, "drawingarea1"));
        gtk_widget_queue_draw(da1);
        return TRUE; //para rearmar o timeout
}


