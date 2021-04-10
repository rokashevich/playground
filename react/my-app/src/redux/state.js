let state = {
  profilePage: {
    posts: [
      { id: 1, message: 'Hi, how are you?', likesCount: 10 },
      { id: 2, message: "It's my first post", likesCount: 12 },
      { id: 3, message: 'Second post!', likesCount: 1000 },
      { id: 4, message: 'Fourth post!', likesCount: 4 }
    ]
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

export let addPost = postMessage => {
  let newPost = {
    id: 5,
    message: postMessage
  }
  state.profilePage.posts.push(newPost)
}
export default state
