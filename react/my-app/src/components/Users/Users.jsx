import { NavLink } from 'react-router-dom'
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
        {pages
          .map(p => (
            <span className={p % 2 === 0 ? s.even : s.odd} key={p}>
              <span
                className={props.currentPage === p ? s.selectedPage : s.page}
                onClick={() => {
                  props.onPageChanged(p)
                }}>
                {p}
              </span>
            </span>
          ))
          .reverse()}
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
              disabled={props.followingInProgress.some(id => id === u.id)}
              onClick={() => {
                props.unfollow(u.id)
              }}>
              Unfollow
            </button>
          ) : (
            <button
              disabled={props.followingInProgress.some(id => id === u.id)}
              onClick={() => {
                props.follow(u.id)
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
