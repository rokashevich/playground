const SEND_MESSAGE = 'SEND-MESSAGE'
const UPDATE_NEW_MESSAGE_BODY = 'UPDATE-NEW-MESSAGE-BODY'
let initialState = {
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
  ],
  newMessageBody: ''
}
const dialogsReducer = (state = initialState, action) => {
  switch (action.type) {
    case UPDATE_NEW_MESSAGE_BODY: {
      let stateCopy = { ...state }
      stateCopy.newMessageBody = action.body
      return stateCopy
    }
    case SEND_MESSAGE: {
      let stateCopy = { ...state }
      stateCopy.messages = [...state.messages]
      let body = stateCopy.newMessageBody
      stateCopy.messages.push({
        id: 6,
        message: body
      })
      stateCopy.newMessageBody = ''
      return stateCopy
    }
    default:
      return state
  }
}
export const sendMessageCreator = () => ({
  type: SEND_MESSAGE
})

export const updateNewMessageBodyCreator = body => ({
  type: UPDATE_NEW_MESSAGE_BODY,
  body: body
})
export default dialogsReducer
