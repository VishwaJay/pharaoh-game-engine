
/*! $Id$
 *  @file   PgeSDLWindowSystem.cpp
 *  @author Chad M. Draper
 *  @date   May 14, 2008
 *
 */

#include "PgeSDLWindowSystem.h"

namespace PGE
{

    SDLWindowSystem::SDLWindowSystem()
    {
        //ctor
    }

    SDLWindowSystem::~SDLWindowSystem()
    {
        //dtor
        SDL_Quit();
    }

    //Init----------------------------------------------------------------------
    void SDLWindowSystem::Init()
    {
        // Register SDL_Quit to be called at exit
        atexit( SDL_Quit );

        // Initialize the video
        if ( SDL_Init( SDL_INIT_VIDEO ) )
        {
            String msg = std::string( "Unable to initialize SDL: " ) + SDL_GetError();
            throw Exception( msg );
        }

        // Create a window with the specified height and width:
        SetSize( mWidth, mHeight );
        if ( !mSurface )
        {
            String msg = std::string( "Unable to setup video: " ) + SDL_GetError();
            throw Exception( msg );
        }

        // Perform any additional initialization required by the sub-classed engine
        AdditionalInit();
    }

    //HandleInput---------------------------------------------------------------
    void SDLWindowSystem::HandleInput()
    {
        SDL_Event event;
        while ( SDL_PollEvent( &event ) )
        {
            switch ( event.type )
            {
            case SDL_KEYDOWN:
                {
                    // If the escape key was pressed, terminate the application.
                    // All other key processing gets passed to the derived class.
                    if ( event.key.keysym.sym == SDLK_ESCAPE )
                    {
                        mQuit = true;
                        break;
                    }

                    KeyDown( event.key.keysym.sym );
                }
                break;

            case SDL_KEYUP:
                KeyUp( event.key.keysym.sym );
                break;

            case SDL_QUIT:
                mQuit = true;
                break;

            case SDL_MOUSEMOTION:
                MouseMove( event.button.button,
                            event.motion.x,
                            event.motion.y,
                            event.motion.xrel,
                            event.motion.yrel );
                break;

            case SDL_MOUSEBUTTONUP:
                MouseButtonUp( event.button.button,
                            event.motion.x,
                            event.motion.y,
                            event.motion.xrel,
                            event.motion.yrel );
                break;

            case SDL_MOUSEBUTTONDOWN:
                MouseButtonDown( event.button.button,
                            event.motion.x,
                            event.motion.y,
                            event.motion.xrel,
                            event.motion.yrel );
                break;

            case SDL_ACTIVEEVENT:
                if ( event.active.state & SDL_APPACTIVE )
                {
                    if ( event.active.gain )
                    {
                        mIsMinimized = false;
                        MakeActive();
                    }
                    else
                    {
                        mIsMinimized = true;
                        MakeInactive();
                    }
                }
                break;
            }
        }
    }

    // CreateSurface------------------------------------------------------------
    void SDLWindowSystem::CreateSurface()
    {
        mSurface = SDL_SetVideoMode( mWidth, mHeight, 0, SDL_SWSURFACE );
    }

    //SetTitle------------------------------------------------------------------
    void SDLWindowSystem::SetTitle( const String& title )
    {
        BaseWindowSystem::SetTitle( title );

        SDL_WM_SetCaption( mTitle.c_str(), 0 );
    }

    //LockSurface---------------------------------------------------------------
    void SDLWindowSystem::LockSurface()
    {
        // Fill the background:
        SDL_FillRect( mSurface, 0, SDL_MapRGB( mSurface->format, 0, 0, 0 ) );

        // Lock surface if necessary:
        if ( SDL_MUSTLOCK( mSurface ) )
        {
            if ( SDL_LockSurface( mSurface ) < 0 )
                return;
        }
    }

    //LockSurface---------------------------------------------------------------
    void SDLWindowSystem::UnlockSurface()
    {
        // Unlock the surface:
        if ( SDL_MUSTLOCK( mSurface ) )
        {
            SDL_UnlockSurface( mSurface );
        }

        // Update the screen:
        SDL_Flip( mSurface );
    }

} // namespace PGE
