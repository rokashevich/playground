import React from 'react'
import DialogItem from './DialogItem/DialogItem'
import Message from './Message/Message'
import s from './Dialogs.module.css'

const Dialogs = props => {
  let dialogsElements = props.dialogs.map(e => (
    <DialogItem name={e.name} id={e.id} />
  ))
  let messagesElements = props.messages.map(e => (
    <Message message={e.message} />
  ))
  return (
    <div className={s.dialogs}>
      <div className={s.dialogsItems}>{dialogsElements}</div>
      <div className={s.messages}>{messagesElements}</div>
    </div>
  )
}

export default Dialogs
