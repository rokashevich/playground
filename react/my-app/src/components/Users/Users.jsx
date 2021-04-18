import React from 'react'
import s from './Users.module.css'
import * as axios from 'axios'
import userPhoto from '../../assets/images/user.png'

class User extends React.Component {
  constructor(props) {
    super(props)
    this.getUsers()
    axios
      .get('https://social-network.samuraijs.com/api/1.0/users')
      .then(response => this.props.setUsers(response.data.items))
  }
  getUsers = () => {}
  render() {
    return (
      <div>
        {this.props.users.map(u => (
          <div key={u.id}>
            <span>
              <div>
                <img
                  alt='ava'
                  src={u.photos.small != null ? u.photos.small : userPhoto}
                  className={s.userPhoto}
                />
              </div>
              {u.followed ? (
                <button onClick={() => this.props.unfollow(u.id)}>
                  Unfollow
                </button>
              ) : (
                <button onClick={() => this.props.follow(u.id)}>Follow</button>
              )}
            </span>
            <span>
              <span>
                <div>{u.name}</div>
                <div>{u.status}</div>
              </span>
              <span>
                <div>{'u.location.contry'}</div>
                <div>{'u.location.city'}</div>
              </span>
            </span>
          </div>
        ))}
      </div>
    )
  }
}
export default User
