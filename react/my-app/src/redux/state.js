let store = {
  _state: {
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
  },
  _callSubscriber() {
    console.log('state changed')
  },
  getState() {
    return this._state
  },
  subscribe(observer) {
    this._callSubscriber = observer
  },
  dispatch(action) {
    if (action.type === 'ADD-POST') {
      let newPost = {
        id: 5,
        message: this.getState().profilePage.newPostText,
        likesCount: 0
      }
      this._state.profilePage.posts.push(newPost)
      this._state.profilePage.newPostText = ''
      this._callSubscriber(this._state)
    } else if (action.type === 'UPDATE-NEW-POST-TEXT') {
      this._state.profilePage.newPostText = action.newText
      this._callSubscriber(this._state)
    }
  }
}

window.store = store

export default store
