for (int i = length-1; i >= 0; i--)
        {
            if(i==0)
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            }
             SDL_FRect rect1 ={(float)body[i].x,(float)body[i].y,(float)body[i].w,(float)body[i].h};
             SDL_RenderFillRect(renderer, &rect1);
        }
