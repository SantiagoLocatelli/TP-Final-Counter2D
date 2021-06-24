#include "sdl_tile.h"

Tile::Tile(int x, int y, int tileType){
    //Get the offsets
    this->mBox.x = x;
    this->mBox.y = y;

    //Set the collision box
    this->mBox.w = TILE_WIDTH;
    this->mBox.h = TILE_HEIGHT;

    //Get the tile type
    this->mType = tileType;
}

void Tile::render(SDL_Rect& camera){
    //If the tile is on screen
    //if (checkCollision(camera, this->mBox)){ // esto es para ir renderizando las tails que hay en pantalla nada mas
        //Show the tile
        SdlTexture::render(this->mBox.x - camera.x, this->mBox.y - camera.y, &gTileClips[this->mType]);
    //}
}

int Tile::getType(){
    return mType;
}

SDL_Rect Tile::getBox(){
    return mBox;
}






Tile::Tile( int x, int y, int tileType )
{
    //Get the offsets
    mBox.x = x;
    mBox.y = y;

    //Set the collision box
    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;

    //Get the tile type
    mType = tileType;
}


void Tile::render(SDL_Rect& camera){
    //If the tile is on screen
    //if (checkCollision(camera, mBox)){
        //Show the tile
        gTileTexture.render(mBox.x - camera.x, mBox.y - camera.y, &gTileClips[ mType ]);
    //}
}


int Tile::getType()
{
    return mType;
}

SDL_Rect Tile::getBox()
{
    return mBox;
}


void put_tile( Tile *tiles[], int tileType, SDL_Rect& camera )
{
    //Mouse offsets
    int x = 0, y = 0;
    
    //Get mouse offsets
    SDL_GetMouseState( &x, &y );
    
    //Adjust to camera
    x += camera.x;
    y += camera.y;
	//Go through tiles
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        //Get tile's collision box
        SDL_Rect box = tiles[ t ]->getBox();
        
        //If the mouse is inside the tile
        if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
        {
            //Get rid of old tile
            delete tiles[ t ];
            
            //Replace it with new one
            tiles[ t ] = new Tile( box.x, box.y, tileType );
        }
    }
}

bool loadMedia( Tile* tiles[] )
{
	//Loading success flag
	bool success = true;

	//Load tile texture
	if( !gTileTexture.loadFromFile( "39_tiling/tiles.png" ) )
	{
		printf( "Failed to load tile set texture!\n" );
		success = false;
	}

	//Load tile map
	if( !setTiles( tiles ) )
	{
		printf( "Failed to load tile set!\n" );
		success = false;
	}

	return success;
}

void close( Tile* tiles[] )
{
	//Deallocate tiles
	for( int i = 0; i < TOTAL_TILES; ++i )
	{
		 if( tiles[ i ] != NULL )
		 {
			delete tiles[ i ];
			tiles[ i ] = NULL;
		 }
	}
}

bool setTiles( Tile* tiles[] )
{
	//Success flag
	bool tilesLoaded = true;

    //The tile offsets
    int x = 0, y = 0;

    //Open the map
    std::ifstream map( "39_tiling/lazy.map" );

    //If the map couldn't be loaded
    if( map.fail())
    {
		//Initialize the tiles
        for( int t = 0; t < TOTAL_TILES; t++ )
        {
            //Put a floor tile
            tiles[ t ] = new Tile( x, y, t % ( TILE_BLUE + 1 ) );
            
            //Move to next tile spot
            x += TILE_WIDTH;
        
            //If we've gone too far
            if( x >= LEVEL_WIDTH )
            {
                //Move back
                x = 0;
            
                //Move to the next row
                y += TILE_HEIGHT;    
            }
        }
    }
	else
	{
		//Initialize the tiles
		for( int i = 0; i < TOTAL_TILES; ++i )
		{
			//Determines what kind of tile will be made
			int tileType = -1;

			//Read tile from map file
			map >> tileType;

			//If the was a problem in reading the map
			if( map.fail() )
			{
				//Stop loading map
				printf( "Error loading map: Unexpected end of file!\n" );
				tilesLoaded = false;
				break;
			}

			//If the number is a valid tile number
			if( ( tileType >= 0 ) && ( tileType < TOTAL_TILE_SPRITES ) )
			{
				tiles[ i ] = new Tile( x, y, tileType );
			}
			//If we don't recognize the tile type
			else
			{
				//Stop loading map
				printf( "Error loading map: Invalid tile type at %d!\n", i );
				tilesLoaded = false;
				break;
			}

			//Move to next tile spot
			x += TILE_WIDTH;

			//If we've gone too far
			if( x >= LEVEL_WIDTH )
			{
				//Move back
				x = 0;

				//Move to the next row
				y += TILE_HEIGHT;
			}
		}
		
		//Clip the sprite sheet
		if( tilesLoaded )
		{
			gTileClips[ TILE_RED ].x = 0;
			gTileClips[ TILE_RED ].y = 0;
			gTileClips[ TILE_RED ].w = TILE_WIDTH;
			gTileClips[ TILE_RED ].h = TILE_HEIGHT;

			gTileClips[ TILE_GREEN ].x = 0;
			gTileClips[ TILE_GREEN ].y = 80;
			gTileClips[ TILE_GREEN ].w = TILE_WIDTH;
			gTileClips[ TILE_GREEN ].h = TILE_HEIGHT;

			gTileClips[ TILE_BLUE ].x = 0;
			gTileClips[ TILE_BLUE ].y = 160;
			gTileClips[ TILE_BLUE ].w = TILE_WIDTH;
			gTileClips[ TILE_BLUE ].h = TILE_HEIGHT;

			gTileClips[ TILE_TOPLEFT ].x = 80;
			gTileClips[ TILE_TOPLEFT ].y = 0;
			gTileClips[ TILE_TOPLEFT ].w = TILE_WIDTH;
			gTileClips[ TILE_TOPLEFT ].h = TILE_HEIGHT;

			gTileClips[ TILE_LEFT ].x = 80;
			gTileClips[ TILE_LEFT ].y = 80;
			gTileClips[ TILE_LEFT ].w = TILE_WIDTH;
			gTileClips[ TILE_LEFT ].h = TILE_HEIGHT;

			gTileClips[ TILE_BOTTOMLEFT ].x = 80;
			gTileClips[ TILE_BOTTOMLEFT ].y = 160;
			gTileClips[ TILE_BOTTOMLEFT ].w = TILE_WIDTH;
			gTileClips[ TILE_BOTTOMLEFT ].h = TILE_HEIGHT;

			gTileClips[ TILE_TOP ].x = 160;
			gTileClips[ TILE_TOP ].y = 0;
			gTileClips[ TILE_TOP ].w = TILE_WIDTH;
			gTileClips[ TILE_TOP ].h = TILE_HEIGHT;

			gTileClips[ TILE_CENTER ].x = 160;
			gTileClips[ TILE_CENTER ].y = 80;
			gTileClips[ TILE_CENTER ].w = TILE_WIDTH;
			gTileClips[ TILE_CENTER ].h = TILE_HEIGHT;

			gTileClips[ TILE_BOTTOM ].x = 160;
			gTileClips[ TILE_BOTTOM ].y = 160;
			gTileClips[ TILE_BOTTOM ].w = TILE_WIDTH;
			gTileClips[ TILE_BOTTOM ].h = TILE_HEIGHT;

			gTileClips[ TILE_TOPRIGHT ].x = 240;
			gTileClips[ TILE_TOPRIGHT ].y = 0;
			gTileClips[ TILE_TOPRIGHT ].w = TILE_WIDTH;
			gTileClips[ TILE_TOPRIGHT ].h = TILE_HEIGHT;

			gTileClips[ TILE_RIGHT ].x = 240;
			gTileClips[ TILE_RIGHT ].y = 80;
			gTileClips[ TILE_RIGHT ].w = TILE_WIDTH;
			gTileClips[ TILE_RIGHT ].h = TILE_HEIGHT;

			gTileClips[ TILE_BOTTOMRIGHT ].x = 240;
			gTileClips[ TILE_BOTTOMRIGHT ].y = 160;
			gTileClips[ TILE_BOTTOMRIGHT ].w = TILE_WIDTH;
			gTileClips[ TILE_BOTTOMRIGHT ].h = TILE_HEIGHT;
		}
	}
}


void save_tiles( Tile *tiles[] )
{
    //Open the map
    std::ofstream map( "39_tiling/lazy.map" );
    
    //Go through the tiles
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        //Write tile type to file
        map << tiles[ t ]->getType() << " ";
    }
    
    //Close the file
    map.close();
}


void show_type( int tileType )
{
    switch( tileType )
    {
        case TILE_RED:
        SDL_SetWindowTitle(gWindow, "Level Designer. Current Tile: Red Floor");
        break;
        
        case TILE_GREEN:
        SDL_SetWindowTitle(gWindow, "Level Designer. Current Tile: Green Floor");
        break;
        
        case TILE_BLUE:
        SDL_SetWindowTitle(gWindow, "Level Designer. Current Tile: Blue Floor");
        break;
        
        case TILE_CENTER:
        SDL_SetWindowTitle(gWindow, "Level Designer. Current Tile: Center Wall");
        break;
        
        case TILE_TOP:
        SDL_SetWindowTitle(gWindow, "Level Designer. Current Tile: Top Wall");
        break;
        
        case TILE_TOPRIGHT:
        SDL_SetWindowTitle( gWindow,"Level Designer. Current Tile: Top Right Wall");
        break;
        
        case TILE_RIGHT:
        SDL_SetWindowTitle(gWindow, "Level Designer. Current Tile: Right Wall");
        break;
        
        case TILE_BOTTOMRIGHT:
        SDL_SetWindowTitle( gWindow,"Level Designer. Current Tile: Bottom Right Wall");
        break;
        
        case TILE_BOTTOM:
        SDL_SetWindowTitle(gWindow, "Level Designer. Current Tile: Bottom Wall");
        break;
        
        case TILE_BOTTOMLEFT:
        SDL_SetWindowTitle( gWindow,"Level Designer. Current Tile: Bottom Left Wall");
        break;
        
        case TILE_LEFT:
        SDL_SetWindowTitle(gWindow, "Level Designer. Current Tile: Left Wall");
        break;
        
        case TILE_TOPLEFT:
        SDL_SetWindowTitle( gWindow,"Level Designer. Current Tile: Top Left Wall");
        break;
    };    
}


bool touchesWall( SDL_Rect box, Tile* tiles[] )
{
    //Go through the tiles
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        //If the tile is a wall type tile
        if( ( tiles[ i ]->getType() >= TILE_CENTER ) && ( tiles[ i ]->getType() <= TILE_TOPLEFT ) )
        {
            //If the collision box touches the wall tile
            if( checkCollision( box, tiles[ i ]->getBox() ) )
            {
                return true;
            }
        }
    }

    //If no wall tiles were touched
    return false;
}
