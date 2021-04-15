import React from 'react'
import DialogItem from './DialogItem/DialogItem'
import Message from './Message/Message'
import s from './Dialogs.module.css'

const Dialogs = props => {
  let state = props.dialogsPage
  let dialogsElements = state.dialogs.map(e => (
    <DialogItem name={e.name} id={e.id} />
  ))
  let messagesElements = state.messages.map(e => (
    <Message message={e.message} />
  ))
  let messageBody = state.newMessageBody
  let onSendMessageClick = () => {
    props.sendMessage()
  }
  let onNewMessageChange = e => {
    let body = e.target.value // сообщение которое попытались ввести
    props.updateNewMessageBody(body)
  }
  return (
    <div className={s.dialogs}>
      <div className={s.dialogsItems}>{dialogsElements}</div>
      <div className={s.messages}>
        <div>{messagesElements}</div>
        <div>
          <div>
            <textarea
              value={messageBody}
              onChange={onNewMessageChange}
              placeholder='Enter your message'></textarea>
          </div>
          <div>
            <button onClick={onSendMessageClick}>Send</button>
          </div>
        </div>
      </div>
    </div>
  )
}

export default Dialogs
