import s from './Users.module.css'
import userPhoto from '../../assets/images/user.png'
import { NavLink } from 'react-router-dom'
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
          <span
            className={props.currentPage === p ? s.selectedPage : s.page}
            onClick={() => {
              props.onPageChanged(p)
            }}>
            {p}
          </span>
        ))}
      </div>
      {props.users.map(u => (
        <div key={u.id}>
          <span>
            <div>
              <NavLink to={'/profile/' + u.id}>
                <img
                  alt='ava'
                  src={u.photos.small != null ? u.photos.small : userPhoto}
                  className={s.userPhoto}
                />
              </NavLink>
            </div>
            {u.followed ? (
              <button onClick={() => props.unfollow(u.id)}>Unfollow</button>
            ) : (
              <button onClick={() => props.follow(u.id)}>Follow</button>
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
export default Users
