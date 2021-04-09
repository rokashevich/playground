import React from 'react'
import s from './ProfileInfo.module.css'

const ProfileInfo = () => {
  return (
    <div>
      <div>
        <img
          alt='from internet'
          height='100px'
          src='https://wallpapercave.com/wp/wp2173645.jpg'></img>
      </div>
      <div className={s.descriptionBlock}>ava + desc</div>
    </div>
  )
}

export default ProfileInfo
