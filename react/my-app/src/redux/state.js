let rerenderEntireTree = () => {
  console.log('state changed')
}
let state = {
  profilePage: {
    posts: [
      { id: 1, message: 'Hi, how are you?', likesCount: 10 },
      { id: 2, message: "It's my first post", likesCount: 12 },
      { id: 3, message: 'Second post!', likesCount: 1000 },
      { id: 4, message: 'Fourth post!', likesCount: 4 }
    ],
    newPostText: 'it-camasutra.com'
  },
  dialogsPage: {
    messages: [
      { id: 1, message: 'Hi' },
      { id: 2, message: 'LOL' },
      { id: 3, message: 'Hellow' },
      { id: 4, message: 'Eee!' },
      { id: 5, message: 'Привет!' }
    ],
    dialogs: [
      { id: 1, name: 'Dimych' },
      { id: 2, name: 'Andrey' },
      { id: 3, name: 'Sveta' },
      { id: 4, name: 'Sasha' },
      { id: 5, name: 'Viktor' }
    ]
  }
}

window.state = state

export let addPost = () => {
  let newPost = {
    id: 5,
    message: state.profilePage.newPostText,
    likesCount: 0
  }
  state.profilePage.posts.push(newPost)
  state.profilePage.newPostText = ''
  rerenderEntireTree(state)
}

export const subscribe = observer => {
  rerenderEntireTree = observer
}

export let updateNewPostText = newText => {
  state.profilePage.newPostText = newText
  rerenderEntireTree(state)
}

export default state
