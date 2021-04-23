import { NavLink } from 'react-router-dom'
import axios from 'axios'
import s from './Users.module.css'
import userPhoto from '../../assets/images/user.png'
let Users = props => {
  let pagesCount = Math.ceil(props.totalUsersCount / props.pageSize)
  let pages = []
  for (let i = 1; i <= pagesCount; i++) {
    pages.push(i)
  }
  return (
    <div>
      <div className={s.pagination}>
        {pages.map(p => (
          <span>
            <span
              className={props.currentPage === p ? s.selectedPage : s.page}
              onClick={() => {
                props.onPageChanged(p)
              }}>
              {p}
            </span>
            &nbsp;
          </span>
        ))}
      </div>
      {props.users.map(u => (
        <div key={u.id}>
          <NavLink to={'/profile/' + u.id}>
            <img
              alt='ava'
              src={u.photos.small != null ? u.photos.small : userPhoto}
              className={s.userPhoto}
            />
          </NavLink>
          {u.followed ? (
            <button
              onClick={() => {
                axios
                  .delete(
                    `https://social-network.samuraijs.com/api/1.0/follow/${u.id}`,
                    {
                      withCredentials: true,
                      headers: {
                        'API-KEY': 'c4b4c099-00c8-43ae-b1f9-65ae19e7d6ae'
                      }
                    }
                  )
                  .then(response => {
                    if (response.data.resultCode === 0) {
                      props.unfollow(u.id)
                    }
                  })
              }}>
              Unfollow
            </button>
          ) : (
            <button
              onClick={() => {
                axios
                  .post(
                    `https://social-network.samuraijs.com/api/1.0/follow/${u.id}`,
                    {},
                    {
                      withCredentials: true,
                      headers: {
                        'API-KEY': 'c4b4c099-00c8-43ae-b1f9-65ae19e7d6ae'
                      }
                    }
                  )
                  .then(response => {
                    if (response.data.resultCode === 0) {
                      props.follow(u.id)
                    }
                  })
              }}>
              Follow
            </button>
          )}
          {u.id} {u.name}
          {u.status}
        </div>
      ))}
    </div>
  )
}
export default Users
