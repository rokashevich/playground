import React from 'react'
import s from './Users.module.css'
import * as axios from 'axios'
import userPhoto from '../../assets/images/user.png'

class User extends React.Component {
  componentDidMount() {
    axios
      .get(
        `https://social-network.samuraijs.com/api/1.0/users?page=${this.props.currentPage}&count=${this.props.pageSize}`
      )
      .then(response => {
        this.props.setUsers(response.data.items)
        this.props.setUsersCount(response.data.totalCount)
      })
  }

  onPageChanged = pageNumber => {
    this.props.setCurrentPage(pageNumber)
    axios
      .get(
        `https://social-network.samuraijs.com/api/1.0/users?page=${pageNumber}&count=${this.props.pageSize}`
      )
      .then(response => this.props.setUsers(response.data.items))
  }

  render() {
    let pagesCount = Math.ceil(this.props.totalUsersCount / this.props.pageSize)
    let pages = []
    for (let i = 1; i <= pagesCount; i++) {
      pages.push(i)
    }
    return (
      <div>
        <div className={s.pagination}>
          {pages.map(p => (
            <span
              className={this.props.currentPage === p ? s.selectedPage : s.page}
              onClick={() => {
                this.onPageChanged(p)
              }}>
              {p}
            </span>
          ))}
        </div>
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
