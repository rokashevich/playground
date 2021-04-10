import React from 'react'
import ReactDOM from 'react-dom'
import './index.css'
import App from './App'
import reportWebVitals from './reportWebVitals'

let posts = [
  { id: 1, message: 'Hi, how are you?', likesCount: 10 },
  { id: 2, message: "It's my first post", likesCount: 12 },
  { id: 3, message: 'Second post!', likesCount: 1000 },
  { id: 4, message: 'Fourth post!', likesCount: 4 }
]
let dialogs = [
  { id: 1, name: 'Dimych' },
  { id: 2, name: 'Andrey' },
  { id: 3, name: 'Sveta' },
  { id: 4, name: 'Sasha' },
  { id: 5, name: 'Viktor' }
]
let messages = [
  { id: 1, message: 'Hi' },
  { id: 2, message: 'LOL' },
  { id: 3, message: 'Hellow' },
  { id: 4, message: 'Eee!' },
  { id: 5, message: 'Привет!' }
]

ReactDOM.render(
  <React.StrictMode>
    <App posts={posts} dialogs={dialogs} messages={messages} />
  </React.StrictMode>,
  document.getElementById('root')
)

// If you want to start measuring performance in your app, pass a function
// to log results (for example: reportWebVitals(console.log))
// or send to an analytics endpoint. Learn more: https://bit.ly/CRA-vitals
reportWebVitals()
