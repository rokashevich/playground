import React from 'react'
import MyPosts from './MyPosts/MyPosts'
import s from './Profile.module.css'

const Profile = () => {
    return     <div className={s.content}>
    <div>
      <img height='100px' src='https://wallpapercave.com/wp/wp2173645.jpg'></img>
    </div>
    <div>ava + desc</div>
    <MyPosts/>
  </div>
}

export default Profile