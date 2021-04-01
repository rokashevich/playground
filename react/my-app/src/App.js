import React from 'react'
import './App.css';
import Header from './Header'
import Technologies from './Technologies'

const App = () => {
  return <div className='app-wrapper'>
    <header className='header'>
      <img src='https://yt3.ggpht.com/ytc/AAUvwnhcOYdTa8LLrCrXBvmGL2kd1pP1xiGLChGUaz4KGA=s48-c-k-c0x00ffffff-no-rj'></img>
    </header>
    <nav className='nav'>
      <div><a>Profile</a></div>
      <div><a>Messages</a></div>
      <div><a>News</a></div>
      <div><a>Music</a></div>
      <div><a>Settings</a></div>
    </nav>
    <div className='content'>
      <div>
        <img height='100px' src='https://wallpapercave.com/wp/wp2173645.jpg'></img>
      </div>
      <div>ava + desc</div>
      <div>
        my posts
        <div>new post</div>
        <div>
          <div>post 1</div>
          <div>post 2</div>
          <div>post 3</div>
        </div>
      </div>
    </div>
  </div >
}

export default App;

