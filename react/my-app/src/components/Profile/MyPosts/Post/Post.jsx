import React from 'react'
import s from './Post.module.css'

const Post = (props) => {
    return <div className={s.item}>
      <img src='https://img1.looper.com/img/gallery/robocop-sequel-loses-director-neill-blomkamp/intro-1565879277.jpg'></img>
      {props.message}
      <div><span>like ({props.likesCount})</span></div>
      </div>
}

export default Post