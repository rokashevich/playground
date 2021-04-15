import React from 'react'
import s from './MyPosts.module.css'
import Post from './Post/Post'
import {
  addPostActionCreator,
  updateNewPostTextActionCreator
} from '../../../redux/profile-reducer'

const MyPosts = props => {
  let postsElements = props.posts.map(e => (
    <Post message={e.message} likesCount={e.likesCount} />
  ))

  let newPostElement = React.createRef()

  let onAddPost = () => {
    props.addPost()
  }

  let onPostChange = () => {
    let text = newPostElement.current.value
    props.updateNewPostText(text)
  }

  return (
    <div className={s.postsBlock}>
      <h3>My Posts</h3>
      <div>
        <div>
          <textarea
            onChange={onPostChange}
            ref={newPostElement}
            value={props.newPostText}></textarea>
        </div>
        <div>
          <button onClick={onAddPost}>Add post</button>
        </div>
      </div>
      <div className={s.posts}>{postsElements}</div>
    </div>
  )
}

export default MyPosts
