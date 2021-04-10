import React from 'react'
import s from './MyPosts.module.css'
import Post from './Post/Post'

const MyPosts = props => {
  let postsElements = props.posts.map(e => (
    <Post message={e.message} likesCount={e.likesCount} />
  ))
  return (
    <div className={s.postsBlock}>
      <h3>My Posts</h3>
      <div>
        <div>
          <textarea></textarea>
        </div>
        <div>
          <button>Add post</button>
        </div>
      </div>
      <div className={s.posts}>{postsElements}</div>
    </div>
  )
}

export default MyPosts
