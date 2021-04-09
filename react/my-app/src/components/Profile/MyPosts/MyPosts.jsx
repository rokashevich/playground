import React from 'react'
import s from './MyPosts.module.css'
import Post from './Post/Post'

const MyPosts = () => {
  let posts = [
    { id: 1, message: 'Hi, how are you?', likesCount: 10 },
    { id: 2, message: "It's my first post", likesCount: 12 },
    { id: 3, message: 'Second post!', likesCount: 1000 },
    { id: 4, message: 'Fourth post!', likesCount: 4 }
  ]
  let postsElements = posts.map(e => (
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
