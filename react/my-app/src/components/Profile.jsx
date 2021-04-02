import React from 'react'
import s from './Profile.module.css'

const Profile = () => {
    return     <div className={s.content}>
    <div>
      <img height='100px' src='https://wallpapercave.com/wp/wp2173645.jpg'></img>
    </div>
    <div>ava + desc</div>
    <div>
      my posts
      <div>new post</div>
      <div className={s.posts}>
        <div className={s.item}>post 1</div>
        <div className={s.item}>post 2</div>
        <div className={s.item}>post 3</div>
      </div>
    </div>
  </div>
}

export default Profile