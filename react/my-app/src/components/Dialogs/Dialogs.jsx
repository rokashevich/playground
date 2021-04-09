import React from 'react'
import { NavLink } from 'react-router-dom'
import s from './Dialogs.module.css'

const DialogItem = props => {
  return (
    <div className={s.dialog + ' ' + s.active}>
      <NavLink to={'/dialogs/' + props.id}>{props.name}</NavLink>
    </div>
  )
}
const Message = props => {
  return <div className={s.message}>{props.message}</div>
}
const Dialogs = props => {
  let dialogs = [
    { id: 1, name: 'Dimych' },
    { id: 2, name: 'Andrey' },
    { id: 3, name: 'Sveta' },
    { id: 4, name: 'Sasha' },
    { id: 5, name: 'Viktor' }
  ]
  let dialogsElements = dialogs.map(e => <DialogItem name={e.name} id={e.id} />)

  let messages = [
    { id: 1, message: 'Hi' },
    { id: 2, message: 'LOL' },
    { id: 3, message: 'Hellow' },
    { id: 4, message: 'Eee!' },
    { id: 5, message: 'Привет!' }
  ]
  let messagesElements = messages.map(e => <Message message={e.message} />)
  return (
    <div className={s.dialogs}>
      <div className={s.dialogsItems}>{dialogsElements}</div>
      <div className={s.messages}>{messagesElements}</div>
    </div>
  )
}

export default Dialogs
